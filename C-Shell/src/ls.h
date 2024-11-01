#ifndef __LS_H
#define __LS_H

void listfiles(char *path, bool a);             //list files in normal format
void listfilesl(char *path, bool a);            //list files in long format
void ls(char *command);                         //parse and getopt of ls command  
void gettotal(char *path,bool a);               //total in -l
int greaterthan6months(struct tm *present, struct tm *mod); //check if greater than 6 months


#endif