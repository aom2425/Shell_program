#include "ErrorCheck.h"
#include <errno.h>
#include <sys/wait.h>


pid_t ErrorCheck::error_fork(){
	pid_t pid = fork();
	error_check_no_exit((pid < 0), "fork");
	return pid;
}
void ErrorCheck::zombie_harvest(int status){
	while (waitpid(-1, &status, WNOHANG))
		printf("zombie harvested\n");
}


void ErrorCheck::error_check_no_exit(bool argument, const char *message){
	if(argument) perror(message);
}
//kazkur yra klaida nes po prasto iraso neiseina Exitint
void ErrorCheck::exit_success(bool argument, const char *message){
	if(argument){
		printf("%s", message);
		exit(EXIT_SUCCESS);
		//exit(1);
	}
}

void ErrorCheck::error_check(bool argument, const char *message){
	if(argument){
		perror(message);
		exit(EXIT_FAILURE);
	}
}

void ErrorCheck::error_check(void *argument, const char *message){
	if(!argument){
		perror(message);
		exit(EXIT_FAILURE);
	}
}

void ErrorCheck::error_execv(char *path, char **args){
	error_check_no_exit(
		(execv(path, args) && errno != ENOENT),"execv");
}

int ErrorCheck::error_open(char *arg, bool is_des){
//	int open(char*, int, int);
	int fd;
	if(is_des) fd = open(arg, O_RDWR | O_CREAT | O_TRUNC | S_IRWXU, 0644);
	else fd = open(arg, O_RDONLY);
	error_check((fd < 0), "open ");
	return fd;
}

void ErrorCheck::error_close(int fd){
	error_check(close(fd), "close");
}

int ErrorCheck::error_dup2(int oldfd, int newfd){
	int fd = dup2(oldfd, newfd);
	error_check((fd < 0), "dup2");
	return fd;
}

void ErrorCheck::error_change_dir(char* cmd){
	int change = chdir(cmd);
	error_check_no_exit((change<0),  "chdir");
}

void ErrorCheck::error_pipe(int pipes[2]){
		error_check((pipe(pipes)<0), "pipe");
}
