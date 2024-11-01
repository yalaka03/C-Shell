#include "headers.h"

void ctrl_c()
{
    int x;
    if (foreground_true == 0)
        return;
    else
    {
        kill(foreground_pid, SIGINT);
    }
}

void ctrl_z()
{
    if (foreground_true == 0)
        return;
    else
    {
        char filename[20];
        int x;
        char path[100];
        sprintf(path, "/proc/%d/stat", foreground_pid);
        FILE *exe;
        exe = fopen(path, "r");
        if (exe == NULL)
        {
            printf("Some error occured while opening proc file.\n");
            return;
        }
        fscanf(exe, "%d ", &x);
        fscanf(exe, "%s ", filename);
        fclose(exe);
        insertinbglist(foreground_pid,filename);
        setpgid(foreground_pid,foreground_pid);
        kill(foreground_pid, SIGTSTP);
    }
}
