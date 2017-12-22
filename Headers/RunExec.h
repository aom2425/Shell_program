#ifndef RUNEXEC_H
#define RUNEXEC_H

#include "HandleInput.h"
#include "ErrorCheck.h"
#include "Imports.h"

class RunExec{
public:
  static int run_execv(vector<char*> paths, char** cmds);
  static void fork_n_execv(char** cmds);
  static const char* convertStringDownC(string word);
  static char* convertConstCharDown(const char* letters);
  static char* convertStringDown(string word);
  static char *appendPaths(char*head, char*tail);
  static string getPath();
  static char* splitPath(string split);
  static vector<string> listEnviron(char* comingIn);
};

#endif
