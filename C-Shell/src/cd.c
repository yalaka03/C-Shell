#include "headers.h"
#include "cd.h"

void ChangeDirectory(char *dir_to_goto)
{
    if(dir_to_goto==NULL)
    {
        chdir(home_dir);
        ChangePromptDir();
    }
    else if(dir_to_goto=="~")
    {
        chdir(home_dir);
        prompt_dir[0]='~';
        prompt_dir[1]='\0';

    }
    
    else if(chdir(dir_to_goto)<0)
    {
        perror("error");
        return;
    }
    else
    {
        ChangePromptDir();
    }
}
void GetHomeDir()
{
    getcwd(home_dir,sizeof(home_dir));
}
void ChangePromptDir()
{
    char temp[100];
    getcwd(temp,sizeof(temp));
    if(strlen(temp)>=strlen(home_dir)&&strncmp(temp,home_dir,strlen(home_dir)-1)==0)
    {
        strcpy(&prompt_dir[1],&temp[strlen(home_dir)]);
        prompt_dir[0]='~';
    }
    else
    {
        strcpy(prompt_dir,temp);
    }
}


