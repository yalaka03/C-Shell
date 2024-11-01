#ifndef __NON_USER_H
#define __NON_USER_H

void foreground(char* command);                       //executes foreground processes
int background(char command[],char*s);                //executes background processes
void non_user(char command[]);                        //checks if background or foreground to be implemnted
void insertinbglist(int pid,char*s);
int deleteinbglist(int pid);
void Initialisebglist();

struct background_process{
    int pid;
    char name[20];
    int pos;
}bginfo[10];

bool foreground_true;
int foreground_pid;
int shell_pid;



#endif