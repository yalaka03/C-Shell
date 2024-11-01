#include "headers.h"
void sortbgjobs()
{
   for (int i = 0; i < 9; ++i)
   {
      for (int j = 0; j < 10 - i - 1; ++j)
      {
         if (strcmp(bginfo[i + j].name, bginfo[i + j + 1].name) > 0)
         {
            struct background_process temp;
            temp = bginfo[i + j];
            bginfo[i + j] = bginfo[i + j + 1];
            bginfo[i + j + 1] = temp;
         }
      }
   }
}
void printjobs(char *command)
{
   char *args[5];
   char *l = " ";
   char *path = ".";
   int x = 0;
   bool r, s;
   r = s = 0;
   args[0] = strtok(command, l);
   while (args[x] != NULL)
   {
      ++x;
      args[x] = strtok(NULL, l);
   }
   for (int i = 1; i < x; ++i)
   {
      if (args[i][0] == '-')
      {
         if (args[i][1] == 'r' || args[i][2] == 'r')
            r = 1;
         if (args[i][1] == 's' || args[i][2] == 's')
            s = 1;
      }
   }
   if(s==0 && r==0)
   s=r=1;
   sortbgjobs();
   for (int i = 0; i < 10; ++i)
   {
      if (bginfo[i].pid == 0)
         continue;

      char path[100];
      char filename[20];
      FILE *exe;
      int x;
      char state;
      sprintf(path, "/proc/%d/stat", bginfo[i].pid);
      exe = fopen(path, "r");
      if (exe == NULL)
      {
         printf("Process died");
      }
      fscanf(exe, "%d ", &x);
      fscanf(exe, "%s ", filename);
      fscanf(exe, "%c ", &state);
      fclose(exe);
      if((state=='t'||state=='T')&&s)
      {
         printf("[%d] Stopped %s [%d]\n",bginfo[i].pos,filename,bginfo[i].pid);
      }
      else if (!(state=='t'||state=='T')&&s)
      {
         printf("[%d] Running %s [%d]\n",bginfo[i].pos,filename,bginfo[i].pid);
      }
   }
}