#include "headers.h"
#include "non_user.h"

void Initialisebglist()
{
   bool foreground_true=0;
   for (int i = 0; i < 10; ++i)
   {
      
      bginfo[i].pid = 0;
      bginfo[i].name[0] = '\0';
      bginfo[i].pos=-1;
      
   }
}
void insertinbglist(int pid, char *s)
{
   int i;
   int x=0;
   for (i = 0; i < 10; ++i)
   {
      if (bginfo[i].pid == 0)
      {
         bginfo[i].pid = pid;
         strcpy(bginfo[i].name,s);
         break;
      }
   }
   for (int j = 0; j < 10; ++j)
   {
      if (bginfo[j].pid != 0)
      {
         ++x;
      }
   }
   

   if (i == 9)
   {
      printf("background queue full,data not stored\n");
      return;
   }

   bginfo[i].pos=x;
}
int deleteinbglist(int pid)
{
   int i;
   int deleted=0;
   for (i = 0; i < 10; ++i)
   {
      if (bginfo[i].pid == pid)
      {
         char *s="\0";
         bginfo[i].pid = 0;
         strcpy(bginfo[i].name,s);
         deleted=1;
         break;
      }
   }

   for(int j=0;j<10;++j)
   {
      if(bginfo[j].pos>bginfo[i].pos)
      bginfo[j].pos--;
   }
   bginfo[i].pos=-1;
   return deleted;
   
}

void foreground(char *command)
{
   int fork_return;
   char *argv[10];
   char *s = " ";
   int x = 0;
   argv[0] = strtok(command, s);

   while (argv[x] != NULL)
   {
      ++x;
      argv[x] = strtok(NULL, s);
   }
   
   fork_return = fork();
   if(fork_return<0)
   {
   printf("ERROR:Could not fork");
   return;
   }
   if (fork_return == 0)
   {
      execvp(argv[0], argv);
   }
   else
   {
      int status;
      foreground_pid=fork_return;
      foreground_true=1;
      waitpid(fork_return,&status,WUNTRACED);
      foreground_true=0;
      return;
   }
}
int background(char command[], char *name)
{
   int fork_return;
   char *argv[10];
   char *s = " ";
   char *amp = "&";
   int x = 0;
   argv[0] = strtok(command, s);
   
   while (argv[x] != NULL)
   {
      ++x;
      argv[x] = strtok(NULL, s);
      
   }
   
   fork_return = fork();
   insertinbglist(fork_return,argv[0]);
   if(fork_return<0)
   return -1;
   
   if (fork_return == 0)
   {
      setpgid(0,0);
      execvp(argv[0], argv);
   }
   else
   {
      printf("%d\n",fork_return);
      sleep(1);
      char path[30];
      if(fork_return<0)
      return fork_return;
      
      sprintf(path, "/proc/%d/stat", fork_return);
      FILE *exe;
      
      exe = fopen(path, "r");
      if(exe==NULL)
      {

         return fork_return;
      }
      int x=deleteinbglist(fork_return);
      fscanf(exe, "%d",&x);
      fscanf(exe, "%s", name);
      if(x)
      insertinbglist(fork_return,name);
      return fork_return;
   }
}
void non_user(char command[])
{

   
   bool back = 0;
   int x=strlen(command);
   for(int i=0;i<x;++i)
   {
      if(command[i]=='&')
      {
      back=1;
      command[i]=' ';
      break;
      }
   }
   
   if (back)
   {
      char process_name[20];
      int pid = background(command, process_name);
      
      if(pid<0)
      {
         printf("Error:Could not start process\n");
      }
      
      
   }
   else
      foreground(command);
}

