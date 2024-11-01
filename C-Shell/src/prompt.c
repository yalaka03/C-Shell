#include"headers.h"
#include "prompt.h"
#include"cd.h"

char host_name[100];
char username[30];

void DisplayPrompt()
{
    printf("%s@",username);
    printf("%s:",host_name);
    printf("%s",prompt_dir);
    printf("$");
    
}
void InitialisePrompt()
{
    
 gethostname(host_name,30);
 struct stat st;
 stat(home_dir,&st);
 struct passwd *user = getpwuid(st.st_uid);
 strcpy(username,user->pw_name);
 prompt_dir[0]='~';
 prompt_dir[1]='\0';
    
}
// int main()
// {
//     InitialisePrompt();
//     DisplayPrompt();
// }