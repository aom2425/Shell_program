#include "Pipe.h"

/*
first closes the read
second dude closes thre write

/**/

void Pipe::single_pipe(vector<char**> cmds){
  int status;
  int pipe_one[2];
  ErrorCheck::error_pipe(pipe_one);
  pid_t pid = fork();
  if(pid == 0){
    cout << "welcome child " << endl;
    exec_pipe_one(cmds.at(1), pipe_one);
    //erase
    cmds.erase(cmds.begin(), cmds.end());
    exit(-1);
  }
  if(pid > 0){
    cout << "welcome parent " << endl;
    exec_pipe_zero(cmds.at(0), pipe_one);
    cmds.erase(cmds.begin(), cmds.end());
    int r;
    do{
      r = waitpid(-1, &status, WNOHANG);
    }while(r >= 0);
  }
    //else while(wait(&status) != -1);
  /*if(ErrorCheck::error_fork() > 0){
    cout << "welcome parent " << endl;
  }
  else while(wait(&status) != -1);
  /**/

}

void Pipe::exec_pipe_one(char** cmds, int pipe_one[2]){
  cout << "came to child "<< endl;
  ErrorCheck::error_close(pipe_one[0]);
  cout << "closed child successfuly " << endl;
  ErrorCheck::error_dup2(pipe_one[1], WRITE);
  cout << "came to childs dub2 one " << endl;
  cout << "before child exec "<< endl;
  RunExec::run_execv_pipe(
    HandleInput::split_controller(RunExec::splitPath(RunExec::getPath())),
    cmds
  );
  cout << "after child exec " << endl;

}/**/
void Pipe::exec_pipe_zero(char** cmds, int pipe_one[2]){
  cout << "came to parent "<< endl;
  ErrorCheck::error_close(pipe_one[1]);
  cout << "closed parent successfuly " << endl;
  ErrorCheck::error_dup2(pipe_one[0], READ);
  cout << "came to dub2 of parent " << endl;
  //ErrorCheck::error_close(pipe_one[1]);
  cout << "before parent exec "<< endl;
  RunExec::run_execv_pipe(
    HandleInput::split_controller(RunExec::splitPath(RunExec::getPath())),
    cmds
  );
  cout << "after parent exec " << endl;
}

vector<char**> Pipe::clean_pipes(char* input){
  vector<char**> clean;
  vector<char*> dirty = HandleInput::breakdown(input, "|");
  while(!dirty.empty()){
        cout << "checking dirty " << dirty.at(0)<< endl;
        clean.push_back(HandleInput::breakdown(dirty.at(0)).data());
        cout << "clean in while loop" << clean.at(0) << endl;
        dirty.erase(dirty.begin());
  }
  //cout << "clean after loop " << clean << endl;
  return clean;
}
void Pipe::run_pipe(char* input){
  cout << "run_pipe runs " << endl;
      //multi_pipe(clean_pipes(input));
    single_pipe(clean_pipes(input));
}









/*


void Pipe::exec_pipe_three(char** cmds, int pipe_two[2]){
  cout << "came to pipe three "<< endl;
  ErrorCheck::error_dup2(pipe_two[0], READ);
  cout << "came to close three " << endl;
  ErrorCheck::error_close(pipe_two[0]);
  ErrorCheck::error_close(pipe_two[1]);
  cout << "before trird exec "<< endl;
  RunExec::run_execv(
    HandleInput::split_controller(RunExec::splitPath(RunExec::getPath())),
    cmds
  );
}


void Pipe::multi_pipe(vector<char**> cmds){
  int pipe_one[2], pipe_two[2];
  ErrorCheck::error_pipe(pipe_one);
  if(ErrorCheck::error_fork()==0){
    //exec
    cout << "first fork " << endl;
    exec_pipe_one(cmds.at(0), pipe_one);
  }
  ErrorCheck::error_pipe(pipe_two);
  if(ErrorCheck::error_fork()==0){
    //exec
    cout << "second fork " << endl;
    exec_pipe_two(cmds.at(1), pipe_one, pipe_two);
  }
  ErrorCheck::error_close(pipe_one[0]);
  ErrorCheck::error_close(pipe_one[1]);
  if(ErrorCheck::error_fork()==0){
    //exec
    cout << "thrid fork " << endl;
    exec_pipe_three(cmds.at(2), pipe_two);
  }
}
void Pipe::exec_pipe_two(char** cmds, int pipe_one[2], int pipe_two[2]){
  cout << "came to pipe two "<< endl;
  ErrorCheck::error_dup2(pipe_one[0], READ);
  ErrorCheck::error_dup2(pipe_two[1], WRITE);
  cout << "came to close two " << endl;
  ErrorCheck::error_close(pipe_one[0]);
  ErrorCheck::error_close(pipe_one[1]);
  ErrorCheck::error_close(pipe_two[0]);
  ErrorCheck::error_close(pipe_two[1]);

  cout << "before second exec "<< endl;
  RunExec::run_execv(
    HandleInput::split_controller(RunExec::splitPath(RunExec::getPath())),
    cmds
  );
}





void Pipe::single_pipe(vector<char**> cmds){
  int status;

    int pipe_one[2];
    pipe(pipe_one);
    //ErrorCheck::error_pipe(pipe_one);
    pid_t pid = fork();
    if(pid == 0){
        //erase cmds.erase(cmds.begin(), cmds.end())
      //exec_pipe_one(cmds.at(0), pipe_one);
      cout << "came to child "<< endl;
      ErrorCheck::error_close(pipe_one[0]);
      cout << "closed child successfuly " << endl;
      ErrorCheck::error_dup2(pipe_one[1], WRITE);
      cout << "came to childs dub2 one " << endl;
      //ErrorCheck::error_close(pipe_one[1]);
      cout << "before child exec "<< endl;
      RunExec::run_execv_pipe(
         HandleInput::split_controller(RunExec::splitPath(RunExec::getPath())),
        cmds
      );
      cout << "after child exec " << endl;
    }
    else if(pid > 0){
      //exec_pipe_two(cmds.at(0), pipe_one);
      cout << "came to parent "<< endl;
      ErrorCheck::error_close(pipe_one[1]);
      cout << "closed parent successfuly " << endl;
      ErrorCheck::error_dup2(pipe_one[0], READ);
      cout << "came to dub2 of parent " << endl;
      //ErrorCheck::error_close(pipe_one[1]);

      cout << "before parent exec "<< endl;
      /*RunExec::run_execv_pipe(
        HandleInput::split_controller(RunExec::splitPath(RunExec::getPath())),
        cmds
      );
      cout << "after parent exec " << endl;
    }
    else{
      perror("fork failed:");
    }
    //ErrorCheck::error_pipe(pipe_one);
    //cout << "error pipe " << ErrorCheck::error_fork() << endl;
    /*if(ErrorCheck::error_fork()==0){
      //exec
      cout << "child " << endl;
      exec_pipe_one(cmds.at(0), pipe_one);
    }
    if(ErrorCheck::error_fork()>0){
      //exec
      cout << "parent " << endl;
      exec_pipe_two(cmds.at(1), pipe_one);
    }
}
/**/
/*
void Pipe::exec_pipe_one(char** cmds, int pipe_one[2]){
  cout << "piping first " << endl;
  ErrorCheck::error_close(pipe_one[0]);
}/**/
/*
void Pipe::exec_pipe_one(char** cmds, int pipe_one[2]){
  cout << "came to child "<< endl;
  ErrorCheck::error_close(pipe_one[0]);
  cout << "closed child successfuly " << endl;
  ErrorCheck::error_dup2(pipe_one[1], WRITE);
  cout << "came to childs dub2 one " << endl;
  //ErrorCheck::error_close(pipe_one[1]);
  cout << "before child exec "<< endl;
  RunExec::run_execv_pipe(
    HandleInput::split_controller(RunExec::splitPath(RunExec::getPath())),
    cmds
  );
  cout << "after child exec " << endl;

}/**/
/*
void Pipe::exec_pipe_two(char** cmds, int pipe_one[2]){
  cout << "came to parent "<< endl;
  ErrorCheck::error_close(pipe_one[1]);
  cout << "closed parent successfuly " << endl;
  ErrorCheck::error_dup2(pipe_one[0], READ);
  cout << "came to dub2 of parent " << endl;
  ErrorCheck::error_close(pipe_one[1]);

  cout << "before parent exec "<< endl;
  RunExec::run_execv_pipe(
    HandleInput::split_controller(RunExec::splitPath(RunExec::getPath())),
    cmds
  );
  cout << "after parent exec " << endl;
}



vector<char**> Pipe::clean_pipes(char* input){
  vector<char**> clean;
  vector<char*> dirty = HandleInput::breakdown(input, "|");
  while(!dirty.empty()){
        cout << "checking dirty " << dirty.at(0) << "hello"<< endl;
        clean.push_back(HandleInput::breakdown(dirty.at(0)).data());
        cout << "clean in while loop" << clean.at(0) << endl;
        dirty.erase(dirty.begin());
  }
  //cout << "clean after loop " << clean << endl;
  return clean;
}

void Pipe::run_pipe(char* input){
  cout << "run_pipe runs " << endl;
      //multi_pipe(clean_pipes(input));
    single_pipe(clean_pipes(input));
}


/**/
