#include "command.h"

////////////////////////////////////////////////////////////////////////
//  사용자 정의 명령을 처리하는 함수
////////////////////////////////////////////////////////////////////////
int shellcmd(int argc, char *argv[])
{
	char *path;
	int flag = 1;

	// ls
	if(!strcmp(argv[0], "ls"))
	{
		cmd_ls(argc, argv);
	}
	// pwd
	else if(!strcmp(argv[0], "pwd"))
	{
		cmd_pwd();
	}
	// cd
	else if(!strcmp(argv[0], "cd"))
	{
		cmd_cd(argc, argv);
	}
		// mkdir
	else if(!strcmp(argv[0], "mkdir"))
	{
		cmd_mkdir(argc, argv);
	}
	// rmdir
	else if(!strcmp(argv[0], "rmdir"))
	{
		cmd_rmdir(argc, argv);
	}
	// ln
	else if(!strcmp(argv[0], "ln"))
	{
		cmd_ln(argc, argv);
	}
	// cp
	else if(!strcmp(argv[0], "cp"))
	{
		cmd_cp(argc, argv);
	}
	// rm
	else if(!strcmp(argv[0], "rm"))
	{
		cmd_rm(argc, argv);
	}
	// mv
	else if(!strcmp(argv[0], "mv"))
	{
		cmd_mv(argc, argv);
	}
	// cat
	else if(!strcmp(argv[0], "cat"))
	{
		cmd_cat(argc, argv);
	}
	//백그라운드
	else if ( !strcmp(argv[argc-1], "&") )
	{
			demon(argv[0]);
	}
	else if( !strcmp(argv[0], "sleep") )
	{
		
		int i = 0;
		
		printf("sleep for %d sec(s).\n",i);
		
	}
	// exit
	else if( !strcmp(argv[0], "exit") )
	{
		printf("***EXIT MINI SHELL**\n");
		exit(4); // 종료 상태가 4이면 반복문 탈출. 쉘 종료
	} 
	else
	{
			flag = 0;
	}
	
	return flag;
}

/////////////////////////////////////////////////
// 자식 프로세스에서 실행되는 함수 
/////////////////////////////////////////////////
void execute(int argc, char *argv[])
{

		int flag;

		signal_int();
		signal_quit();

		if( !shellcmd(argc, argv))
		{
			// 사용자 정의 명령이 아닌 경우 
			printf("no cmd function\n");
			printf("ls, pwd, cd, mkdir, rmdir, ln, cp, rm, mv, cat\n");
		}
	
	//exit(1);
}

