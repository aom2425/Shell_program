//https://brennan.io/2015/01/16/write-a-shell-in-c/
//http://users.cs.cf.ac.uk/Dave.Marshall/C/node20.html
//http://cc.byexamples.com/2008/06/16/gnu-readline-implement-custom-auto-complete/
//http://www.math.utah.edu/docs/info/rlman_2.html#SEC36
//http://www.delorie.com/gnu/docs/readline/hist_15.html
//https://gist.github.com/mplewis/5279108
//https://stackoverflow.com/questions/876605/multiple-child-process
/*
 m  p
[x][x]  1  /bin/ls
[x][x]  1  ls
[][]  2  PATH=
[x][x]  2  ls $HOME
[x][x]  2  QUEUE +1
[x][X]  2  PS1
[x][x]  1  ctrl+l
[x][x]  2  tabcompletion+history
[x][x]  1  History
[x][x]  1  redirect >
[x][x]  1  redirect <
[x][x]  1  users
[x][x]  1  ctrl c
[x][x]  1  ~
[~][]   3  &
[][]   2  piping
[x][x]  1  !commands
[x][x]  1  !num
19
/**/
/*
TO FIX:


/**/
#include "Shell.h"

Shell *Shell::shell_instance = NULL;
main(int argc, char **argv){
  Shell::instance();
  //Shell *shell = new Shell();
  //delete[] shell;
  return 0;
}
