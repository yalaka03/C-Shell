#include "headers.h"
#include "pinfo.h"
#include "cd.h"
#include "non_user.h"
void getrelativepath(char path[])
{

   if (strlen(path) >= strlen(home_dir) && strncmp(path, home_dir, strlen(home_dir) - 1) == 0)
   {
      char temp[100];
      strcpy(temp, path);
      strcpy(&path[1], &temp[strlen(home_dir)]);
      path[0]='~';
   }
   return;
}
void pinfo_apply(pid_t pid_shell)
{
   char path[100], buffer[100];
   char filename[20],temp[20];
   printf("pid -- %d\n", pid_shell);
   sprintf(path, "/proc/%d/stat", pid_shell);
   FILE *exe;
   int x;
   char state;
   long unsigned int vm;
   exe = fopen(path, "r");
   if (exe == NULL)
   {
      printf("Invalid pid");
      return;
   }
   fscanf(exe, "%d ", &x);
   fscanf(exe, "%s ", filename);
   fscanf(exe, "%c ", &state);
   for (int i = 0; i < 10; ++i)
   {
      if (bginfo[i].pid == pid_shell)
      {
         printf("state -- %c\n", state);
         state = '\0';
         break;
      }
   }
   if (state != '\0')
      printf("state -- %c+\n", state);
   for (int i = 0; i < 19; ++i)
   {
      fscanf(exe, "%s ", temp);
   }
   fscanf(exe, "%lu", &vm);
   printf("memory -- %lu {virtual memory}\n", vm);
   fclose(exe);
   sprintf(path, "/proc/%d/exe", pid_shell);
   

   x = readlink(path, buffer, 100);
   if(x>0)
   {buffer[x]='\0';
   getrelativepath(buffer);
   printf("Executable path -- %s\n",buffer);
   }
   else
   printf("Executable name %s\n",filename);
   
   
   
}

void pinfo(char command[])
{
   char *token;
   char *s = " ";
   strtok(command, s);
   token = strtok(NULL, s);
   if (token == NULL)
   {
      pinfo_apply(getpid());
   }
   else
   {
      pinfo_apply(atoi(token));
   }
}
