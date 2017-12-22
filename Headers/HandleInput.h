#ifndef HANDLEINPUT_H
#define HANDLEINPUT_H

#include "Imports.h"
#include "ErrorCheck.h"
#include "RunExec.h"
#include "Redirect.h"
#include "Pipe.h"

class HandleInput{
public:
  static char *find_cmd(char* arg, size_t size);
  static void exit_console(char* cmdExit);
  static int ps1_control(char* cmds);
  static char* check_Dirty(char* check);
  static const char* check_Dirty(char* check, const char* delim);
  static vector<char*> breakdown(char*input);
  static vector<char*> breakdown(char*input, const char *delim);
  static char* make_cmdp(char* cmds);
  static int helper_to_getrid(char* input);
  static char* breakIt(char*input);
  static char* getEnvironment(char* cmds);
  static string inject_substring(size_t start, string str, bool tilde);
  static char* handle_tilde(char* cmd, const char* needle);
  static bool check_multiple_tilde(char* cmds);
  static void change_dir(char* cmd);
  static void auto_exe_file(char* cmd);
  static void background_exe(char* cmd);
  static vector<char*> split_controller(char* set);
  static bool command_Switch(char* arg);
};

#endif
