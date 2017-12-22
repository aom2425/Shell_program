#ifndef PIPE_H
#define PIPE_H

#include "RunExec.h"
#include "HandleInput.h"
#include "ErrorCheck.h"
#include "Imports.h"


class Pipe{
public:
  static void multi_pipe(vector<char**> cmds);
  static void single_pipe(vector<char**> cmds);
  static void exec_pipe_one(char** cmds, int pipe_one[2]);
  //static void exec_pipe_two(char** cmds, int pipe_one[2], int pipe_two[2]);
  static void exec_pipe_zero(char** cmds, int pipe_one[2]);
  //static void exec_pipe_three(char** cmds, int pipe_two[2]);
  static vector<char**> clean_pipes(char* input);
  static void run_pipe(char* input);
};

#endif
