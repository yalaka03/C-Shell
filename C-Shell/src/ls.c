#include "headers.h"
#include "ls.h"
#include "cd.h"
void gettotal(char *path,bool a)
{
   DIR *dir;
   dir = opendir(path);
   if (dir == NULL)
      return;
   int total = 0;
   struct dirent *dr;
   char temp[200];
   struct stat st;
   char *c = "/";
   dr = readdir(dir);
   while (dr != NULL)
   {
      strcpy(temp, path);
      if (dr->d_name[0] == '.'&& a==0)
      {
         dr = readdir(dir);
         continue;
      }

      if (dr == NULL)
      {
         continue;
      }
      strcat(temp, c);
      strcat(temp, dr->d_name);
      stat(temp, &st);
      total += st.st_blocks / 2;
      dr = readdir(dir);
   }
   printf("total %d\n", total);
   closedir(dir);
   return;
}
int greaterthan6months(struct tm *present, struct tm *mod)
{
   if (present->tm_mon - mod->tm_mon < 6)
      return 0;
   if (present->tm_mon - mod->tm_mon > 6)
      return 1;
   if (present->tm_mon - mod->tm_mon == 6)
   {
      if (present->tm_mday > mod->tm_mday)
         return 1;
      else
         return 0;
   }
}
void listfiles(char *path, bool a)
{
   struct dirent *dr;
   DIR *dir;
   char *c = "/";
   char buffer[100];
   if (path[0] == '~')
   {
      strcpy(buffer, home_dir);
      goto l1;
   }
   getcwd(buffer, 100);
   strcat(buffer, c);
   strcat(buffer, path);
l1:
   dir = opendir(buffer);
   if (dir == NULL)
   {

      struct stat st;
      if (stat(buffer, &st) == -1)
      {
         perror("Error:");
         return;
      }
      char *file_name = strrchr(buffer, '/');
      printf("%s\n", file_name + 1);
      return;
   }
   dr = readdir(dir);
   while (dr != NULL)
   {
      if (dr->d_name[0] == '.' && a == 0)
      {
         dr = readdir(dir);
         continue;
      }
      else
      {
         printf("%s\n", dr->d_name);
         dr = readdir(dir);
      }
   }
   closedir(dir);
}
void listfilesl(char *path, bool a)
{
   time_t present;
   time(&present);
   struct tm *present_time = localtime(&present);
   struct stat st;
   struct dirent *dr;
   DIR *dir;
   char *c = "/";
   char buffer[200], temp[200];
   if (path[0] == '~')
   {
      strcpy(buffer, home_dir);
      goto l1;
   }
   getcwd(buffer, 200);
   strcat(buffer, c);
   strcat(buffer, path);

l1:
   dir = opendir(buffer);
   if (dir == NULL)
   {

      if (stat(buffer, &st) == -1)
      {
         perror("Error:");
         return;
      }
      char *file_name = strrchr(buffer, '/');
      struct passwd *user = getpwuid(st.st_uid);
      struct group *grp = getgrgid(st.st_gid);

      struct tm *mod_time = localtime(&st.st_mtime);
      char *time;
      time = asctime(mod_time);
      S_ISDIR(st.st_mode) ? printf("d") : printf("-");
      st.st_mode &S_IRUSR ? printf("r") : printf("-");
      st.st_mode &S_IWUSR ? printf("w") : printf("-");
      st.st_mode &S_IXUSR ? printf("x") : printf("-");
      st.st_mode &S_IRGRP ? printf("r") : printf("-");
      st.st_mode &S_IWGRP ? printf("w") : printf("-");
      st.st_mode &S_IXGRP ? printf("x") : printf("-");
      st.st_mode &S_IROTH ? printf("r") : printf("-");
      st.st_mode &S_IWOTH ? printf("w") : printf("-");
      st.st_mode &S_IXOTH ? printf("x ") : printf("- ");
      printf("%ld ", st.st_nlink);
      printf("%s %s ", user->pw_name, grp->gr_name);
      printf("%5ld ", st.st_size);
      for (int i = 0; i < 7; ++i)
      {
         printf("%c", time[4 + i]);
      }
      if (greaterthan6months(present_time, mod_time))
      {
         printf(" ");
         for (int i = 0; i < 4; ++i)
         {
            printf("%c", time[20 + i]);
         }
         printf(" ");
      }
      else
      {
         for (int i = 0; i < 5; ++i)
         {
            printf("%c", time[11 + i]);
         }
      }
      printf(" %s\n", (file_name+1));
      return;
   }
   gettotal(buffer,a);
   dr = readdir(dir);
   while (dr != NULL)
   {
      strcpy(temp, buffer);
      if (dr->d_name[0] == '.' && a == 0)
      {
         dr = readdir(dir);
         continue;
      }
      if (dr == NULL)
      {
         continue;
      }
      strcat(temp, c);
      strcat(temp, dr->d_name);
      stat(temp, &st);
      struct passwd *user = getpwuid(st.st_uid);
      struct group *grp = getgrgid(st.st_gid);

      struct tm *mod_time = localtime(&st.st_mtime);
      char *time;
      time = asctime(mod_time);
      S_ISDIR(st.st_mode) ? printf("d") : printf("-");
      st.st_mode &S_IRUSR ? printf("r") : printf("-");
      st.st_mode &S_IWUSR ? printf("w") : printf("-");
      st.st_mode &S_IXUSR ? printf("x") : printf("-");
      st.st_mode &S_IRGRP ? printf("r") : printf("-");
      st.st_mode &S_IWGRP ? printf("w") : printf("-");
      st.st_mode &S_IXGRP ? printf("x") : printf("-");
      st.st_mode &S_IROTH ? printf("r") : printf("-");
      st.st_mode &S_IWOTH ? printf("w") : printf("-");
      st.st_mode &S_IXOTH ? printf("x ") : printf("- ");
      printf("%ld ", st.st_nlink);
      printf("%s %s ", user->pw_name, grp->gr_name);
      printf("%ld ", st.st_size);
      for (int i = 0; i < 7; ++i)
      {
         printf("%c", time[4 + i]);
      }
      if (greaterthan6months(present_time, mod_time))
      {
         printf(" ");
         for (int i = 0; i < 4; ++i)
         {
            printf("%c", time[20 + i]);
         }
         printf(" ");
      }
      else
      {
         for (int i = 0; i < 5; ++i)
         {
            printf("%c", time[11 + i]);
         }
      }
      printf(" %s\n", dr->d_name);
      dr = readdir(dir);
   }
   closedir(dir);
}

void ls(char *command)
{
   int x = 0, count_paths = 0;
   int opt;
   bool a, l, no_path;
   a = l = 0;
   no_path = 1;
   char *args[10];
   char *s = " ";
   char *path = ".";
   args[0] = strtok(command, s);
   
   while (args[x] != NULL)
   {
      ++x;
      args[x] = strtok(NULL, s);
      
      if (args[x]!=NULL&&args[x][0] != '-')
         ++count_paths;
   }
   
   // while ((opt = getopt(x, args, "al")) != -1)
   // {
   //    switch (opt)
   //    {
   //    case 'a':
   //       a = 1;
   //       break;
   //    case 'l':
   //       l = 1;
   //       break;
   //    }
   // }
   for (int i = 1; i < x; ++i)
   {
      if (args[i][0] == '-')
      {
         if(args[i][1]=='l'||args[i][2]=='l')
         l=1;
         if(args[i][1]=='a'||args[i][2]=='a')
         a=1;

      }
   }
   for (int i = 1; i < x; ++i)
   {
      if (args[i][0] != '-')
      {
         no_path = 0;
         if (count_paths > 1)
            printf("%s:\n", args[i]);
         if (l == 0)
         {
            listfiles(args[i], a);
         }
         else
         {
            listfilesl(args[i], a);
         }
      }
   }
   if (no_path)
   {
      if (l == 0)
      {
         listfiles(path, a);
      }
      else
      {
         listfilesl(path, a);
      }
   }
}

// int main()
// {
//    char command1[30] = "ls -l";
//    ls(command1);
//    char command2[30] = "ls -l";
//    ls(command2);
//    char command3[30] = "ls -l";
//    ls(command3);
// }
