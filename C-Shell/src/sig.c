#include"headers.h"

void sig(char * command)
{
    char*s=" ";
   char*token=strtok(command,s);
   token=strtok(NULL,s);
   int pos=atoi(token);
   token=strtok(NULL,s);
   int signal_id=atoi(token);
   for(int i=0;i<10;++i)
   {
       if(pos==bginfo[i].pos)
       {
           kill(bginfo[i].pid,signal_id);
           break;
       }
       if(i==9)
       {
           printf("Job  Position not found");
       }
   }
   return;
}