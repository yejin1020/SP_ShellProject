#include <signal.h>
#include "command.h"

//////////////////////////////////////////////////////
// 자식 프로세스의 SIGINT, SIGQUIT의 차단을 해제 하는 함수
//////////////////////////////////////////////////////

void handler_int(int signo){
    printf("\nSIGINT ON\n");
    pid_t ppid = getppid();
    kill(ppid, SIGINT);
}

void handler_quit(int signo){
    printf("\nSIGQUIT ON\n");
    pid_t ppid = getppid();
    kill(ppid, SIGQUIT);
}

void signal_int(){
    struct sigaction sig_int;
    sig_int.sa_handler = handler_int; 
    sigfillset(&(sig_int.sa_mask)); 
    sigaction(SIGINT, &sig_int, NULL);
}

void signal_quit(){
    struct sigaction sig_quit;
    sig_quit.sa_handler = handler_quit;
    sigfillset(&(sig_quit.sa_mask));
    sigaction(SIGQUIT, &sig_quit, NULL);
}

/////////////////////////////////////////////////
// 부모 프로세스의 SIGINT, SIGQUIT를 차단하는 함수
/////////////////////////////////////////////////
void blocksignal()
{
	sigset_t set2;
	
	sigemptyset(&set2);
	sigaddset(&set2, SIGQUIT);//set up set2 with just SIGINT
	sigaddset(&set2, SIGINT);//set up set2 with just SIGINT  
	sigprocmask(SIG_BLOCK, &set2, NULL);// unblock SIGINT 
	
}
