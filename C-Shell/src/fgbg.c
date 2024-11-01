#include "headers.h"

void fg(char *command)
{
    char *s = " ";
    char *token = strtok(command, s);
    token = strtok(NULL, s);
    if (token == NULL)
    {
        printf("No job number given, please give one\n");
    }
    int job_id = atoi(token);
    int pid;
    for (int i = 0; i < 10; ++i)
    {
        if (job_id == bginfo[i].pos)
        {
            pid = bginfo[i].pid;
            break;
        }
        if (i == 9)
        {
            printf("No job exists with given number.");
            return;
        }
    }
    deleteinbglist(pid);
    foreground_pid = pid;
    foreground_true = 1;
    signal(SIGTTOU,SIG_IGN);
    signal(SIGTTIN,SIG_IGN);
    
    tcsetpgrp(STDOUT_FILENO,pid);
    setpgid(0,pid);
    kill(pid, SIGCONT);
    waitpid(pid, &job_id, WUNTRACED);
    setpgid(0,0);
    tcsetpgrp(STDOUT_FILENO,getpid());
    foreground_true = 0;
    signal(SIGTTOU,SIG_DFL);
    signal(SIGTTIN,SIG_DFL);
    return;
}

void bg(char *command)
{
    char *s = " ";
    char *token = strtok(command, s);
    token = strtok(NULL, s);
    if (token == NULL)
    {
        printf("No job number given, please give one\n");
        return;
    }
    int job_id = atoi(token);
    int pid;
    for (int i = 0; i < 10; ++i)
    {
        if (job_id == bginfo[i].pos)
        {
            pid = bginfo[i].pid;
            break;
        }
        if (i == 9)
        {
            printf("No job exists with given number.");
            return;
        }
    }
    char path[100];
    char filename[20];
    FILE *exe;
    int x;
    char state;
    sprintf(path, "/proc/%d/stat", pid);
    exe = fopen(path, "r");
    if (exe == NULL)
    {
        printf("Process died");
    }
    fscanf(exe, "%d ", &x);
    fscanf(exe, "%s ", filename);
    fscanf(exe, "%c ", &state);
    fclose(exe);

    if (state == 't' || state == 'T')
        kill(pid, SIGCONT);

    return;
}