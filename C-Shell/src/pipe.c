#include "headers.h"

void pipecreator(char *command)
{
    int std_in = dup(STDIN_FILENO);
    int std_out = dup(STDOUT_FILENO);
    
    char *s=strrchr(command,'|');
    *s='\0';
    if (command[strlen(command) - 1] == ' ')
        command[strlen(command) - 1] = '\0';
    int fildes[2];
    if(pipe(fildes)<0)
    {
        perror("error");
        return;
    }
    dup2(fildes[1],STDOUT_FILENO);
    callfunctions(command);
    dup2(std_out,STDOUT_FILENO);
    close(fildes[1]);
    dup2(fildes[0],STDIN_FILENO);
    close(fildes[0]);
    callfunctions((s+2));
    dup2(std_in,STDIN_FILENO);
    close(std_out);
    close(std_in);
}