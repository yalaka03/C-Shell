#include "headers.h"
#include "outinredirect.h"
#include "callfunctions.h"
void outputparser(char *command)
{
    int fd, std_out;
    char *start = strrchr(command, '>');
    std_out = dup(STDOUT_FILENO);
    if (*(start - 1) != '>')
    {
        fd = open(start + 2, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        dup2(fd, STDOUT_FILENO);
        close(fd);
        *(start-1) = '\0';
    }
    else
    {

        fd = open(start + 2, O_CREAT | O_WRONLY | O_APPEND, 0644);
        dup2(fd, STDOUT_FILENO);
        close(fd);
        *(start - 2) = '\0';
    }

    callfunctions(command);
    dup2(std_out, STDOUT_FILENO);
    close(std_out);
}
void inputparser(char *command)// take care of case when more than one file in input 
{
    int fd, std_in;
    char *start = strrchr(command, '<');
    char filename[30];
    char * index=start+2;
    int i=0;
    while(*index!=' '&&*index!='\0')
    {
        filename[i]=*index;
        ++index;
        ++i;
    }
    filename[i]='\0';
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("Error");
        return;
    }
    *start = ' ';
    *(start + 1) = ' ';
    while (*start != ' ' && *start != '\0')
    {
        *start = ' ';
        start++;
    }
    char *s = " ";
    char input_without_spaces[100];
    char *token = strtok(command, s);
    strcpy(input_without_spaces, token);
    while (1)
    {
        token = strtok(NULL, s);

        if (token == NULL)
            break;
        strcat(input_without_spaces, s);
        strcat(input_without_spaces, token);
    }
    strcpy(command,input_without_spaces);
    std_in = dup(STDIN_FILENO);
    dup2(fd, STDIN_FILENO);
    close(fd);
    callfunctions(command);
    dup2(std_in, STDIN_FILENO);
    close(std_in);
}
