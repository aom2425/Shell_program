#include "Redirect.h"

void Redirect::controller(char *input){
	cout << "controller" << endl;
	if(strpbrk(input, ">")) write_o_read(input, WRITE, ">");
	else write_o_read(input, READ, "<");
}

void Redirect::write_o_read(char *input, int action, const char* tok){
  cout << "write to file" <<  endl;
  int status;
  if(ErrorCheck::error_fork() == 0){
    vector<char*> cmds = HandleInput::breakdown(input, tok);
    cmds.at(0) = HandleInput::check_Dirty(cmds.at(0));
    cout << "at 0 " << cmds.at(0) << endl;
    cmds.at(1) =  HandleInput::check_Dirty(cmds.at(1));
    cout << "at 1 " << cmds.at(1) << endl;
    //setup_cmds(HandleInput::breakdown(input, tok.c_str()));
    file_action(action, cmds.at(1));
    cout << "im here one " << endl;
  	RunExec::run_execv(
      HandleInput::split_controller(RunExec::splitPath(RunExec::getPath())),
      HandleInput::breakdown(cmds.at(0)).data()
    );
    cout << "im here two " << endl;
    cmds.clear();
  }else while(wait(&status) != -1);
}

vector<char*> Redirect::setup_cmds(vector<char*> vec){
	cout << "setup commands" << endl;
	vector<char*> list;
	list.push_back(HandleInput::check_Dirty(vec.at(0)));
	list.insert(list.begin(), HandleInput::check_Dirty(vec.at(1)));
	return list;
}

void Redirect::file_action(int action, char* file){
	int fd = ErrorCheck::error_open((file), action);
	ErrorCheck::error_dup2(fd, action);
	ErrorCheck::error_close(fd);
}


void Redirect::file_action(int action, int fd){
	ErrorCheck::error_dup2(fd, action);
	ErrorCheck::error_close(fd);
}
