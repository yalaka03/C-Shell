#ifndef __CD_H
#define __CD_H

void ChangeDirectory(char *dir_to_goto); // actual change
void GetHomeDir();           // call in main at starting once to initialise home_dir
void ChangePromptDir();      // Changing prompt
char home_dir[100];
char prompt_dir[100];

#endif