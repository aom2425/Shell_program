#ifndef IMP_H
#define IMP_H

#include <string.h>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <wordexp.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>

using namespace std;

#define exern char** environ;
#define DELIMS " \t\r\n"
#define WRITE 1
#define READ 0


#endif
