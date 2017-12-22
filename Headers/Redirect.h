#ifndef REDIRECT_H
#define REDIRECT_H

#include "RunExec.h"
#include "ErrorCheck.h"
#include "HandleInput.h"
#include <vector>

#include "Imports.h"

class Redirect{
public:
	static void write_o_read(char *input, int action, const char* tok);
	static void file_action(int action, char* cmds);
	static void file_action(int action, int fd);
	static vector<char*> setup_cmds(vector<char*> vec);
	static void controller(char *direction);
};



#endif
