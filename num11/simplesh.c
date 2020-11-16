/* simplesh.c */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#include "command.h"

int main()
{
	char buf[256];
	char *argv[256];
	int narg;
	pid_t pid;
	int status, exit_status;

	chdir((char*)getenv("HOME"));
	blocksignal(); // 부모 시그널 ctrlc,/차단
	
	while(1) {
	
		
		print_prompt(); // minish 프롬 프트 출력
		
		fgets(buf,sizeof(buf),stdin);
		narg = getargs(buf, argv); // 명령어 분리 

		pid  = fork(); // minish 명령어를 수행할 자식 프로세스 생성

		if( pid == 0 )
		{
			execute(narg,argv);
		}
		else if ( pid >  0 ){
			wait(&status);
		}
		else
			perror("fork error");

		if (WIFEXITED(status)) {
			exit_status = WEXITSTATUS(status); 
			printf("Exit status from %d was %d\n",pid, exit_status);
			if(exit_status == 4)
				break;
		}
		
	}
}

