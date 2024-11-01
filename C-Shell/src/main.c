
#include "headers.h"

void print_info_background() //background process exit displayer
{
    int stat;
    pid_t pid;
    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
    {
        for (int i = 0; i < 10; ++i)
        {
            if (bginfo[i].pid == pid)
            {
                if (bginfo[i].name[0] != '(')
                {
                    if (WIFEXITED(stat) == 1)
                        printf("\n%s with pid %d has exited normally\n", bginfo[i].name, pid);
                    else
                        printf("\n%s with pid %d has exited abnormally\n", bginfo[i].name, pid);
                    deleteinbglist(pid);
                    break;
                }
                char *bracket = ")";
                strtok(bginfo[i].name, bracket);
                if (WIFEXITED(stat) == 1)
                    printf("\n%s with pid %d has exited normally\n", &bginfo[i].name[1], pid);
                else
                    printf("\n%s with pid %d has exited abnormally\n", &bginfo[i].name[1], pid);
                deleteinbglist(pid);
                break;
            }
        }
        fflush(stdout);
    }
    return;
}

int main()
{

    Initialisebglist(); //initialising bg list that keeps track of background proccesses
    GetHomeDir();
    InitialisePrompt(); //initialises prompt
    char *input;
    long unsigned int max_INPUT = 100;
    shell_pid=getpid();
    input = malloc(max_INPUT);
    signal(SIGCHLD, print_info_background); //signal handler for child termination
    signal(SIGINT,ctrl_c);
    signal(SIGTSTP,ctrl_z);
    while (1)
    {

        DisplayPrompt();

        char *s = " ";

        char input_without_spaces[max_INPUT];
        int ctrl_d=getline(&input, &max_INPUT, stdin);
        if(ctrl_d==-1)
        {
            printf("\n");
        callfunctions("exit");
        
        }
        for (int i = 0; input[i] != '\0'; ++i) //making tabs as spaces
        {
            if (input[i] == 9)
            {
                input[i] = ' ';
            }
            if (input[i] == '\n')
                input[i] = '\0';
        }
        char *token = strtok(input, s); //deleting extra tabs and spaces
        if (token == NULL)
            continue;
        strcpy(input_without_spaces, token);
        while (1)
        {
            token = strtok(NULL, s);

            if (token == NULL)
                break;
            strcat(input_without_spaces, s);
            strcat(input_without_spaces, token);
        }
        char command_arr[max_INPUT];
        s = ";";
        int x = 1;
        char *command[10];
        command[0] = strtok(input_without_spaces, s); //tokenising with ;
        while (1)
        {
            command[x] = strtok(NULL, s);
            if (command[x] == NULL)
                break;
            else
                ++x;
        }
        for (int i = 0; i < x; ++i)
        {
            strcpy(command_arr, command[i]);
            if (command_arr[strlen(command_arr) - 1] == ' ')
                command_arr[strlen(command_arr) - 1] = '\0';

            if (command_arr[0] == ' ')
                callfunctions(&command_arr[1]);
            else
                callfunctions(command_arr);
        }
    }
}
