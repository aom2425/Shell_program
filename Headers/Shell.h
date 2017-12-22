#include "Imports.h"
#include "RunExec.h"
#include "HandleInput.h"
#include "ErrorCheck.h"
#include <signal.h>



class Shell{
public:
  static void catch_interupt(int s);
  static Shell *instance(){
    if(!shell_instance)
      shell_instance = new Shell;
    return shell_instance;
  }
  ~Shell(){
    delete[] path;
    delete[] shell_instance;
  }

  void run_command(char** commands);
  void setPrompt(string new_prompt){prompt = new_prompt;};
  void setPrompt(char* new_prompt){prompt = string(new_prompt);};
  void setHome(const char* name){home = getenv(name);}


private:
  string prompt;
  char* home;
  vector<char*> cmds;
  char* path = new char[255];
  const char* his = "/home/gdapkus/pub/CS426/backup/fp/.history";

  void init(char* input, vector<char*> vec);
  char* get_nextline();

  Shell(){
    prompt = string(getenv("USER"))+": ";
    home  = getenv("HOME");
    printf("The\"EXIT\" command will exit shell.\n");
    read_history(his);
    signal (SIGINT, catch_interupt);
    init(get_nextline(), cmds);
  };

protected:
  static Shell *shell_instance;
  void iterate_through(vector<char*> vec);
};
