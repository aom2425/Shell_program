#include "Shell.h"

volatile sig_atomic_t flag = 0;

void Shell::catch_interupt(int s){
  flag = 1;
}/**/

void Shell::init(char *input, vector<char*> vec){

  vec = HandleInput::split_controller(input);
  iterate_through(vec);
  vec.clear();
  //run_command(breakdown(input).data());
  init(get_nextline(), vec);
}

void show_cmds(vector<char*> cmds){
	while(!cmds.empty()){
		cout << cmds.at(0) <<  endl;
		cmds.erase(cmds.begin());
	}
}
char* Shell::get_nextline(){
  char* input = readline(prompt.c_str());
  if(strlen(input) == 0){
			get_nextline();
	}
  else{
    //tab completion is enabled by default
    //if(flag)
    	//		flag = 0;
    char* expandhis[1024];
    if(!strcmp(input, "!"))
      strcpy(input, "!!");
      
	  history_expand(input, expandhis);
	  strcpy(input, expandhis[0]);
    add_history(input);
    write_history(his);
    return input;
  }
}

void Shell::iterate_through(vector<char*> vec){
  if(vec.empty())return;
  cout << "vec " << vec.at(0) << endl;
  //cout << "check " << vec.at(0) << endl;
  if(strstr(vec.at(0), "PS1=")) {
    //cout << "empty1 " << vec.empty()<< endl;
    char* var = HandleInput::breakIt(vec.at(0));
    if(!var){
      printf("improper quotation\n");
    }
    else setPrompt(var);
  }
  else if(!(HandleInput::command_Switch(vec.at(0)))){
    //cout << "it came here " << endl;
    RunExec::fork_n_execv(HandleInput::breakdown(vec.at(0)).data());
  }/**/
  //cout << "empty1 " << vec.size()<< endl;
  vec.erase(vec.begin());
  iterate_through(vec);
}
















/*

void Shell::run_command(char** commands){
  int status;
  strcpy(path, "/bin/");
  strcat(path, commands[0]);
  pid_t pid = fork();
  if(pid < 0){
    perror("pid<0: ");
    exit(1);
  }
  else if(pid == 0){
    if(execv(path, commands) < 0)
      cout  << "Wrong command. Try retyping\n";
  }
  else while(wait(&status) != -1);
}
/**/
/*
if (sh == NULL) {
    fprintf(stderr, "Error eding SHELL env. var.\n");
    return;
}

/* Overwrite env. var. PATH */
/*
if (setenv("PATH", cmd, 1) < 0) {
    fprintf(stderr, "Error setting env. var.\n");
    return;
}
/**/
