#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/utsname.h>
#include <sys/resource.h>
#include <signal.h>
#include <termios.h>
char home_dir[100] = "/home/jazz-blazer/Desktop/IIIT/Sem3/OS&NW";
char prompt_dir[100];
void func1()
{
    int x = 0;
    printf("exited 1");
    exit(x);
}
void func2()
{
    int x = 0;
    printf("exited 2");
    exit(x);
}
void ChangePromptDir()
{
    char temp[100] = "/home/jazz-blazer/Desktop/IIIT/Sem3/OS&NW/Assignment 2/StarterCode";

    if (strlen(temp) > strlen(home_dir) && strncmp(temp, home_dir, strlen(home_dir) - 1) == 0)
    {
        strcpy(&prompt_dir[1], &temp[strlen(home_dir)]);
    }
    else
    {
        strcpy(prompt_dir, temp);
    }
}

int set_tostop(int desc)
{
    struct termios settings;
    int result;

    result = tcgetattr(desc, &settings);
    if (result < 0)
    {
        perror("error in tcgetattr");
        return 0;
    }

    settings.c_lflag &= ~TOSTOP;

    result = tcsetattr(desc, TCSANOW, &settings);
    if (result < 0)
    {
        perror("error in tcsetattr");
        return 0;
    }
    return 1;
}
void signal_handler1()
{
    int x;
    return;
}
void bgfg(int pid)
{
    int stat;
    // signal(SIGTTOU,SIG_BLOCK);
    // signal(SIGTTIN,SIG_BLOCK);
    kill(pid,SIGCONT);
    tcsetpgrp(STDIN_FILENO,pid);
    // signal(SIGTTOU,SIG_UNBLOCK);
    // signal(SIGTTIN,SIG_UNBLOCK);
    waitpid(pid,&stat,WUNTRACED);
    tcsetpgrp(STDIN_FILENO,getpid());
}
int main()
{
    // int fork_return;
    // fork_return=fork();

    // if (fork_return==0)
    // {
    //     signal(SIGTTOU,func1);
    //     printf("hello");
    // }
    // else
    // {
    //     signal(SIGTTOU,func2);

    //     sleep(10);
    //     printf("I slept, see if the above line is printed.");
    // }
    // int stdout;
    // char buff[10]="hello";
    // stdout=dup(STDOUT_FILENO);
    // write(stdout,buff,10);
    // write(STDOUT_FILENO,buff,10);
    // int fd, stdout;
    // stdout = dup(STDIN_FILENO);
    // char buffer[10]="a.txt";
    // fd = open(buffer, O_RDONLY, 0644);
    // dup2(fd, STDIN_FILENO);
    // close(fd);
    // char *args[5];
    // args[0] = "cat";
    // args[1] = NULL;
    // execvp("cat", args);
    // dup2(stdout, STDIN_FILENO);

    // pid_t pid=getpid();
    // pid_t gid=getpgid(0);
    // printf("%d %d\n",gid,pid);
    // int x=fork();
    // if(x==0)
    // {
    //     pid=getpid();
    //     gid=getpgid(0);
    // printf("%d %d",gid,pid);

    // }
    //  char temp[100]="hello | bye";
    //  char *s ="|";
    //  strtok(temp,s);
    //  printf("%s")
    // sleep(100);
    // set_tostop(STDIN_FILENO);
    // signal(SIGTTOU,SIG_IGN);
    // signal(SIGTTIN,SIG_IGN);
    // int fork_return = fork();
    // if (fork_return == 0)
    // {
    //     setpgid(0,0);
    //     // char *argv[5] = {"man", "write", NULL};
    //     // execvp("man", argv);
    //     printf("hello one");
    // }
    // else
    // {
    //     printf("hello too");
    //     sleep(100);
    // }
    // while(1)
    // {
    //     printf("hello\n");
    //     sleep(5);
    // }
    int fork_return;
    fork_return = fork();
    if (fork_return == 0)
    {
        setpgid(0, 0);
        char c[10];
        while (1)
        {
            if (strcmp(c,"e")==0)
                exit(0);
            scanf("%s", c);
            printf("child-%s\n", c);
        }
    }
    else
    {
        signal(SIGTTOU,SIG_IGN);
        signal(SIGTTIN,SIG_IGN);
        char c[10];
        while (1)
        {
            scanf("%s", c);
            if (strcmp(c,"e")==0)
            {
                bgfg(fork_return);
                
            }
            printf("parent-%s\n", c);
        }
    }
}