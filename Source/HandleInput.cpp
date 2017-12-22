#include "HandleInput.h"
//#include "Shell.h"
char *HandleInput::find_cmd(char* arg, size_t size){
  strcpy(arg, (string(arg).substr(size).c_str()));
  return check_Dirty(arg);
}

char* HandleInput::check_Dirty(char* check){
  char *tokken = strdup(check);
	tokken = strtok(tokken, DELIMS);
	if(tokken) return tokken;
	return check;
}

const char* HandleInput::check_Dirty(char* check, const char* delim){
  char *tokken = strdup(check);
	tokken = strtok(tokken, delim);
	if(tokken) return string(tokken).c_str();
	return string(check).c_str();
}

void HandleInput::exit_console(char* cmdExit){
  //cout << "exit_\n";
  ErrorCheck::exit_success(
    (strcmp(check_Dirty(cmdExit), "EXIT")==0),
		"Goodbye, till next time.\n"
		);
}

vector<char*> HandleInput::breakdown(char*input){
	vector<char *> list;
  //cout << "breakdown\n";
  char *split = strtok(input, DELIMS);
  while(split != NULL){
  	list.push_back(split);
  	split = strtok(NULL, DELIMS);
  }
  list.push_back((char *)0);
  return list;
}

vector<char *> HandleInput::breakdown(char *input, const char *delim){
	vector<char *> list;
	//cout << "const breakdown" << endl;
	char *split = strtok(input, delim);
	while(split != NULL){
		list.push_back(split);
		split = strtok(NULL, delim);
	}
	return list;
}

//For PS1
char* HandleInput::breakIt(char*input){
  if(helper_to_getrid(input) % 2 != 0) return NULL;
  return breakdown(input, "\"").at(1);
}
//For PS1
int HandleInput::helper_to_getrid(char* input){
  int count = 0;
  char *split = strstr(input, "\"");
  while(split != NULL){
    count++;
    split+=1;
    split = strstr(split, "\"");
  }
  return count;
}

char* HandleInput::getEnvironment(char* cmds){
   return getenv(check_Dirty(cmds, "$"));
}/**/

void HandleInput::change_dir(char* cmd){
  ErrorCheck::error_change_dir(cmd);
}

/*
char* HandleInput::handle_tilde(char* cmd){
    char* home = getenv("HOME");
    string s = string(cmd);
    size_t pos = strcspn(cmd, "~");  //find where is ~ located
    s.erase(pos, 1);
    s.insert(pos, string( getenv("HOME")));    //insert home directory into s at location of the tilde
    strcpy(cmd, s.c_str());
    return cmd;
}/**/
string HandleInput::inject_substring(size_t start, string str, bool tilde){
	char * sub; size_t stop = str.find(" ", start);
	if(tilde) sub = getenv("HOME");
	if(stop != string::npos){
		if(!tilde) sub = getenv(str.substr(start+1, (stop-start)).c_str());
		return str.replace(start, (stop-start), string(sub));
	}
	if(!tilde) sub = getenv(str.substr(start+1, (stop-start)).c_str());
	return str.replace(start, (str.length()-start), string(sub));
}

char* HandleInput::handle_tilde(char* cmd, const char* needle){
  //cout << "get enviorment" << endl;
	string s = string(cmd);
	size_t start = strcspn(cmd, needle);
	s = inject_substring(start, s, (needle == "~"));
	strcpy(cmd, s.c_str());
	return cmd;
}

vector<char*> HandleInput::split_controller(char* set){
  if(strpbrk(set,":")) return breakdown(set, ":");
	if(strpbrk(set,";")) return breakdown(set, ";");
  return {set};
}
bool HandleInput::check_multiple_tilde(char *cmd){
	char *tilde = strstr(strdup(cmd), "~");
	if(tilde != NULL)
		if(strstr(tilde+1, "~") == NULL || *(tilde+1) == ' ') return true;
	return false;
}
bool HandleInput::command_Switch(char* arg){
  //cout << "command controller" << endl;
  vector<char*> vec;
  if(strpbrk(arg, ">") || strpbrk(arg, "<")) {
    Redirect::controller(arg);
    return true;
  }
  if(strpbrk(arg, "&")) {
    return true;
  }
  if(strpbrk(arg, "|")) {
    //Pipe::run_pipe(arg);
    return true;
  }
  if(strpbrk(arg, "$")) {
    arg = handle_tilde(arg, "$");
  }
  if(strpbrk(arg, "~")){
    while(check_multiple_tilde(arg))
      arg = handle_tilde(arg, "~");
  }
  if(strstr(arg, "cd ")){
    change_dir(find_cmd(arg, 3));
    return true;
  }
  exit_console(arg);
  return false;
}
/**/




/*
if(strpbrk(arg, ". ")){
  //auto_exe_file(find_cmd(arg, 2));
  return true;
}
if(strpbrk(arg, "|")) {
  //  Pipe::run_pipe(arg);
  return true;
}
if(strpbrk(arg, "*")) return true;
/**/


/*
if(strpbrk(arg, "$")){

  vec = breakdown(arg);
  vec.at(1) = getEnvironment(vec.at(1));
  RunExec::fork_n_execv(vec.data());
  return true;
}
/**/

/*
char* HandleInput::handle_tilde(char* cmd){

  wordexp_t wrd;
  size_t len = wordexp(cmd, &wrd, WRDE_NOCMD | WRDE_UNDEF);
  cout << "len " << len << endl;
  if(len)
    return NULL;
  cmd = (char*) malloc(sizeof(char) * (len+1));
  strcpy(cmd, wrd.we_wordv[0]);
  wordfree(&wrd);
  return cmd;
}

/**/

/*void HandleInput::auto_exe_file(char* cmd){
  int fd = ErrorCheck::error_open(cmd);
  ErrorCheck::error_close(fd);
}/**/



//cout << "I am only here " << endl;
  //change_dir(handle_tilde(strstr(arg, "~")));
  //cout << "before " << arg << endl;
  //cout << "after " << arg << endl;
  //return true;

/*void HandleInput::background_exe(char* cmd){
  int first_fork = 0, second_fork = 0;
  int pid_fork_one, pid_fork_two;

  if(first_fork == 0){
    pid_fork_one = ErrorCheck::error_fork();
  }
  if(pid_fork_one == 0){
      first_fork++;
      if(second_fork == 0){
          second_fork++;
          pid_fork_two = ErrorCheck::error_fork();
      }
        //exec proc 1
      if(pid_fork_two == 0){
          RunExec::run_execv(
              HandleInput::split_controller(RunExec::splitPath(RunExec::getPath())),
              HandleInput::breakdown(cmd).data()
          );
          exit(0);
      }
      if(pid_fork_two > 0){
          //zombie
          //exec proc 2
          int status, wait_pid;
          pid_t wait(int *status);
          do{
            wait_pid = waitpid(0, &status, WIFEXITED(status));
          }while(wait_pid > 0);
          usleep(15000);
          RunExec::run_execv(
              HandleInput::split_controller(RunExec::splitPath(RunExec::getPath())),
              HandleInput::breakdown(cmd).data()
          );
          exit(0);
      }
  }
  if(pid_fork_one > 0){
    //zombie
    int status, wait_pid;
    pid_t wait(int *status);
    do{
      wait_pid = waitpid(0, &status, WIFEXITED(status));
    }while(wait_pid > 0);
    usleep(15000);
  }
}
/**/




/*
char *HandleInput::handle_tilde(char* cmd){
  char* converted;
  string convert = string(cmd);
  size_t pos = strcspn(cmd, "~");
  convert.insert(pos, string(getenv("HOME")));
  //convert.replace(convert.begin(), convert.end(),1, '~');
  string convert_this = convert.substr(0, convert.size()-1);
  strcpy(converted, convert_this.c_str());
  return converted;
      //return strcat(getenv("HOME"), find_cmd(cmd, 1));
}/**/
/*
char* HandleInput::handle_tilde(char* cmd){
  char * tilde;
  size_t pos =  string(cmd).find("~");
  cout << "position " << pos << endl;
  tilde = find_cmd(cmd, pos);
  cout << "tilde " << tilde << endl;
  return strcat(getenv("HOME"),  find_cmd(cmd, 1));
}/**/

/*
char* HandleInput::handle_tilde(char* cmd){
    string s = string(cmd);
    //cout << "s char* " << s << endl;
    size_t pos = strcspn(cmd, "~");  //find where is ~ located
    s.erase(pos, 1);
    s.insert(pos, string( getenv("HOME")));   //insert home directory into s at location of the tilde
    //cout << "s " << s << endl;
    strcpy(cmd, s.c_str());
    return cmd;
}/**/
