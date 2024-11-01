#ifndef __PINFO_H
#define __PINFO_H

void pinfo(char command[]);           //call from main
void pinfo_apply(pid_t pid_shell);    //main func that reads /proc files
void getrelativepath(char path[]);    //for executable path

#endif