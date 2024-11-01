#include "headers.h"

void pwd()
{
    char cwd[100];
    char *ch = getcwd(cwd, 100);
    if (ch == NULL)
    {
        perror("Error");
        return;
    }

    printf("%s\n", cwd);
}
