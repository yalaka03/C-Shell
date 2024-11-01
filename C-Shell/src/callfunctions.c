
#include "headers.h"
#include "prompt.h"
#include "pinfo.h"
#include "cd.h"
#include "ls.h"
#include "non_user.h"
#include "echo.h"
#include "pwd.h"
#include "cd.h"
#include "callfunctions.h"
#include "outinredirect.h"

void repeat(char command[]) //repeat command
{
    char temp1[100];
    char *s = " ";
    strcpy(temp1, command);
    strtok(temp1, s);
    char *token = strtok(NULL, s);
    int repeat = atoi(token);
    char *new_command = strchr(&command[7], ' ');
    for (int i = 1; i <= repeat; ++i)
    {
        char temp[100];
        strcpy(temp, new_command + 1);
        callfunctions(temp);
    }
}
void callfunctions(char *command) //calls all implemented and execvc commands
{
    char *inout = strrchr(command, '>');
    if (inout != NULL)
    {
        outputparser(command);
        return;
    }

    inout = strrchr(command, '<');
    if (inout != NULL)
    {
        inputparser(command);
        return;
    }
    char* pipes = strrchr(command,'|');
    if(pipes!=NULL)
    {
        pipecreator(command);
        return;
    }
    char temp[100];
    strcpy(temp, command);
    char *s = " ";
    char *function[] = {"ls", "cd", "pwd", "pinfo", "echo", "exit", "repeat","jobs","sig","fg","bg"};
    char *token = strtok(temp, s);
    char *address = strtok(NULL, s);
    char *token2 = strtok(NULL, s);

    if (strcmp(token, function[0]) == 0)
    {
        ls(command);
    }
    else if (strcmp(token, function[1]) == 0)
    {
        if (token2 != NULL)
        {
            printf("ERROR:Too many arguments\n");
            return;
        }
        ChangeDirectory(address);
    }
    else if (strcmp(token, function[2]) == 0)
    {
        if (address != NULL)
        {
            printf("ERROR:Too many arguments\n");
            return;
        }
        pwd();
    }
    else if (strcmp(token, function[3]) == 0)
    {
        if (token2 != NULL)
        {
            printf("ERROR:Too many arguments\n");
            return;
        }
        pinfo(command);
    }
    else if (strcmp(token, function[4]) == 0)
    {
        echo(command);
    }
    else if (strcmp(token, function[6]) == 0)
    {
        repeat(command);
    }
    else if (strcmp(token, function[5]) == 0)
    {
        exit(0);
    }
    else if (strcmp(token, function[7]) == 0)
    {
        printjobs(command);
    }
    else if (strcmp(token, function[8]) == 0)
    {
        sig(command);
    }
    else if (strcmp(token, function[9]) == 0)
    {
        fg(command);
    }
    else if (strcmp(token, function[10]) == 0)
    {
        bg(command);
    }
    else
    {
        non_user(command);
    }
}