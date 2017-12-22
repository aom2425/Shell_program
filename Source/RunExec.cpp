#include "RunExec.h"

const char *RunExec::convertStringDownC(string word){
	return word.c_str();
}

char* RunExec::convertConstCharDown(const char* letters){
    char *cstr = new char[strlen(letters)+1];
    return strcpy(cstr, letters);
}

char* RunExec::convertStringDown(string word){
  return convertConstCharDown(convertStringDownC(word));
}

char* RunExec::appendPaths(char* head, char* tail){
  return convertStringDown((string(head) + "/" + string(tail)));
}

void RunExec::fork_n_execv(char** cmds){
  int status;
	//cout << "fork_n_execv " << ErrorCheck::error_fork() << endl;
  if(ErrorCheck::error_fork() == 0){
    if(!strstr(cmds[0], "/bin/")){
      vector<char*> paths = HandleInput::split_controller(splitPath(getPath()));
      ErrorCheck::error_check(run_execv(paths, cmds), "execv");
			paths.erase(paths.begin(), paths.end());
    }else{
      vector<char*> v = HandleInput::breakdown(cmds[0], "/bin/");
      v.push_back((char *)0);
      ErrorCheck::error_execv(cmds[0], v.data());
			//v.erase(v.begin(), v.end());
    }
  }
	else while(wait(&status) != -1);
/*
	{
		int r;
		do{
			r = waitpid(-1, &status, WNOHANG);
		}while(r >= 0);
	}//
	/**/
	//while(waitpid (0, &status, WIFEXITED(status))){ usleep(10000);}
}

int RunExec::run_execv(vector<char*> paths, char** cmds){
  if(paths.empty()) return 1;
  ErrorCheck::error_execv(appendPaths(paths.at(0), cmds[0]), cmds);
  paths.erase(paths.begin());
  run_execv(paths, cmds);
}
int RunExec::run_execv_pipe(vector<char*> paths, char** cmds){
	if(paths.empty()) return 1;
	ErrorCheck::error_execv(appendPaths(paths.at(0), cmds[0]), cmds);
	paths.erase(paths.begin());
	run_execv(paths, cmds);
}

//get the whole Path of "PATH="
string RunExec::getPath(){
  int i = 0;
  string str = " ";
  //TODO:USER and HOME for $ COMMAND
  while(environ[i] != NULL){
     if(!(strncmp(environ[i], "PATH=", 5))){
         str = (string)environ[i];
     }
     i++;
  }
  return str;
}
//spliting Path into different lines to acces it one by one
char* RunExec::splitPath(string split){
  char* convert = new char[split.length()+1];
  strcpy(convert, split.c_str());
  return convert;
}
// getting the delimeater and tokenizing it
vector<string> RunExec::listEnviron(char* comingIn){
      int j= 0;
      vector<string> getIn;
      const char* delim = ":";
      char* stringTosplit = strtok(comingIn, delim);
      while(stringTosplit != NULL){
	       getIn.push_back(stringTosplit);
         stringTosplit = strtok(NULL, delim);
         cout << getIn[j];// << "\n";
         j++;
  	  }
      return getIn;
}


/*
else if(!strncmp("PS1=\"", cmds[0], 5)){
  size_t pos = 0;
  cmds += 5;
  while(cmds[pos] != '"')
    ++pos;
}
/**/
