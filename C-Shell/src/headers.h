#include<stdio.h>    
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<dirent.h>
#include<sys/types.h>
#include <pwd.h>
#include <grp.h>
#include<time.h>
#include<stdbool.h>
#include<stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/utsname.h>
#include <sys/resource.h>
#include <signal.h>
#include <termios.h>
#include "prompt.h"
#include "pinfo.h"
#include "cd.h"
#include "ls.h"
#include "non_user.h"
#include "echo.h"
#include "pwd.h"
#include "cd.h"
#include "callfunctions.h"
#include "outinredirect.h"
#include "pipe.h"
#include "jobs.h"
#include "signals.h"
#include "sig.h"
#include "fgbg.h"