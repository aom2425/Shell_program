//#pragma once
#ifndef ERRORCHECK_H
#define ERRORCHECK_H

#include "Imports.h"
#include <readline/readline.h>
#include <readline/history.h>

class ErrorCheck{
public:
  static pid_t error_fork();
  static void error_check_no_exit(bool argument, const char *message);
  static void exit_success(bool argument, const char *message);
  static void error_check(bool argument, const char *message);
  static void error_check(void *argument, const char *message);
  static void error_execv(char *path, char **args);
  static int error_open(char *arg, bool is_des);
  static void error_close(int fd);
	static int error_dup2(int oldfd, int newfd);
  static void readHistory(const char* fileName);
  static void writeHistory(const char* fileName);
  static void error_change_dir(char* cmd);
  static void error_pipe(int pipes[2]);
  static void zombie_harvest(int status);
};
#endif
