#include <signal.h>
#include "command.h"

//////////////////////////////////////////////////////
// 자식 프로세스의 SIGINT, SIGQUIT의 차단을 해제 하는 함수
//////////////////////////////////////////////////////


void signal_int(){
	sigset_t set1;
	sigemptyset(&set1);
	sigaddset(&set1, SIGINT);//set up set2 with just SIGINT 
	sigprocmask(SIG_UNBLOCK, &set1, NULL);// unblock SIGINT
}

void signal_quit(){
	sigset_t set1;
	sigemptyset(&set1);
	sigaddset(&set1, SIGQUIT);//set up set2 with just SIGQUIT 
	sigprocmask(SIG_UNBLOCK, &set1, NULL);// unblock SIGQUIT
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
