#include "command.h"

#define MAX_BUF 128
#define MAX_READ 10

/* minishell의 명령어 함수*/

////////////////////////////////////////////////////////////////////////
//  디렉토리 변경
////////////////////////////////////////////////////////////////////////
void cmd_cd(int argc, char *argv[])
{
	char *path;
	char buf[MAX_BUF];
	
	memset(buf, 0, MAX_BUF);

	if (getcwd(buf, MAX_BUF) < 0) {
		perror("getcwd");
		exit(1);
	}
	printf("working directory (before) = %s\n", buf);

	// 인자가 있을 경우 path를 설정
	if(argc > 1)
	{
		path = argv[1];
	}
	
	// 인자가 없을 경우 HOME디렉토리를 설정
	else if((path = (char*)getenv("HOME")) == NULL)
	{
		// 환경 변수가 없을 경우 현재 디렉토리로 설정
		path = buf;
	}

	// 디렉토리 변경 
	if(chdir(path) < 0)
	{
		perror("chdir");
		exit(1); 
	}
	if (getcwd(buf, MAX_BUF) < 0) {
		perror("getcwd");
		exit(1);
	}
	
	printf("working directory (after ) = %s\n", buf);

}

/////////////////////////////////////////////////////////////////////////
//  현재 경로 출력
////////////////////////////////////////////////////////////////////////
void cmd_pwd()
{

	char buf[MAX_BUF];
	
	memset(buf, 0, MAX_BUF);

	if (getcwd(buf, MAX_BUF) < 0) {
		perror("getcwd");
		exit(1);
	}

	printf("working directory = %s\n", buf);

}


////////////////////////////////////////////////////////////////////////
//  디렉토리 리스트를 출력하는 함수
////////////////////////////////////////////////////////////////////////
void cmd_ls(int argc, char *argv[])
{
	DIR *pdir;
	struct dirent *pde;
	char *path = "."; // 현재 디렉토리
	int count;

	// 디렉토리를 연다.
	if((pdir = opendir(path)) < 0 )
	{
		perror("opendir");
		exit(1);
	
	}

	count = 0;

	// 파일이나 디렉토리를 읽어들인다.
	while((pde = readdir(pdir)) != NULL)
	{
		printf("%20s ", pde->d_name);
		if (++count % 3 == 0)
		printf("\n"); 
	}

	// 디렉토리를 닫는다.
	printf("\n");
	closedir(pdir);

}

////////////////////////////////////////////////////////////////////////
//  파일을 복사하는 함수
////////////////////////////////////////////////////////////////////////
void cmd_cp(int argc, char *argv[])
{
	int src; /* source file descriptor */
	int dst; /* destination file descriptor */
	char buf[10];
	ssize_t rcnt; /* read count */
	ssize_t tot_cnt = 0; /* total write count */ 
	mode_t mode = O_RDWR | O_CREAT | O_TRUNC; 

	// 인자가 2개 이하일 경우 
	if(argc < 3)
	{
		printf("Usage: cp source_file destination_file\n");
		exit(1);
	}

	// 복사할 소스 파일을 연다.
	if ((src = open(argv[1], O_RDONLY)) == -1 ){
		perror("src open"); /* errno에 대응하는 메시지 출력됨 */
		exit(1);
	} 

	// 쓰기를 할 파일을 연다.없다면 생성
 	if ( (dst = open(argv[2], mode , 0644)) == -1 ){
		perror("dst open"); /* errno에 대응하는 메시지 출	력됨 */
		exit(1);
	} 

	// read -> write
	while ( (rcnt = read(src, buf, 10)) > 0) {
		tot_cnt += write(dst, buf, rcnt);
	}

	if (tot_cnt < 0) {
		perror("read");
		exit(1);
	} 

	close(src);
	close(dst);

}

////////////////////////////////////////////////////////////////////////
//  파일 삭제 명령 함수
////////////////////////////////////////////////////////////////////////
void cmd_rm(int argc, char *argv[])
{

	// 인자가 없을 경우 에러
	if(argc < 2)
	{
		fprintf(stderr, " rm filename\n");
		exit(1); 
	}

	// 파일 삭제
	if (unlink(argv[1]) < 0) {
		perror("unlink");
		exit(1);
	} 


}
////////////////////////////////////////////////////////////////////////
//  파일 링크 명령 함수
////////////////////////////////////////////////////////////////////////

void cmd_ln(int argc, char *argv[])
{
	
	char *src;
	char *target;

	// 인자가 없을 경우 에러
	if(argc < 3)
	{
		fprintf(stderr, "ln src target \n");
		exit(1); 
	}

	src = argv[1];
	target = argv[2];

	if (link(src, target) < 0) {
		perror("link");
		exit(1);
	} 
}
////////////////////////////////////////////////////////////////////////
//  파일  이동 명령어
////////////////////////////////////////////////////////////////////////
void cmd_mv(int argc, char *argv[])
{
	struct stat buf;
	char *src_file_name_only;
	char *target;

	if (argc < 3) {
		fprintf(stderr, "Usage: mv src target\n");
		exit(1);
	}

	// Check argv[1] (src) whether it has directory info or not.
	if (access(argv[1], F_OK) < 0) {
		fprintf(stderr, "%s not exists\n", argv[1]);
		exit(1);
	}
	else {
		char *slash = strrchr(argv[1], '/');
		src_file_name_only = argv[1];
		if (slash != NULL) { // argv[1] has directory info.
			src_file_name_only = slash + 1;
		}
	}

	// Make target into a file name if it is a directory
	target = (char *)calloc(strlen(argv[2])+1, sizeof(char));
	strcpy(target, argv[2]);

	if (access(argv[2], F_OK) == 0) {
		if (lstat(argv[2], &buf) < 0) {
			{
				perror("lstat");
				exit(1);
			}
		}
		else {
			if (S_ISDIR(buf.st_mode)) {
				free(target);
				target = (char *) calloc(strlen(argv[1]) +strlen(argv[2]) + 2, sizeof(char));

				strcpy(target, argv[2]);
				strcat(target, "/");
			}
		}
	}

	printf("source = %s\n", argv[1]);
	printf("target = %s\n", target);

	if (rename(argv[1], target) < 0) {
		perror("rename");
		exit(1);
	}

	free(target);



}

////////////////////////////////////////////////////////////////////////
//  디렉토리를 생성하는 함수
////////////////////////////////////////////////////////////////////////
void cmd_mkdir(int argc, char *argv[])
{
	// 인자가 없을 경우 에러
	if(argc < 2)
	{
		fprintf(stderr, "Usage: mkdir dirname\n");
		exit(1); 
	}

	// 디렉토리를 생성한다.
	if(mkdir(argv[1], 0664) < 0)
	{
		fprintf(stderr, "fail to make directiry\n");
		exit(1);
	}

}

////////////////////////////////////////////////////////////////////////
//  디렉토리를 삭제하는 함수
////////////////////////////////////////////////////////////////////////
void cmd_rmdir(int argc, char *argv[])
{
	// 인자가 없을 경우 에러
	if(argc < 2)
	{
		fprintf(stderr, "Usage: rmdir dirname\n");
		exit(1); 
	}

	// 디렉토리를 삭제한다.
	if(rmdir(argv[1]) < 0)
	{
		fprintf(stderr, "fail to remove directiry, directory should be empty\n");
		exit(1);
	}

}

////////////////////////////////////////////////////////////////////////
//  cat 명령어 함수
////////////////////////////////////////////////////////////////////////
void cmd_cat(int argc, char *argv[])
{
	int src; /* source file descriptor */
	int dst; /* destination file descriptor */
	char buf[MAX_READ];
	ssize_t rcnt; /* read count */
	ssize_t tot_cnt = 0; /* total write count */ 
	
	// 인자가 2개 이하일 경우 
	if(argc < 2)
	{
		printf("Usage: cat source_file \n");
		exit(1);
	}

	// 읽을 파일을 연다.
	if ((src = open(argv[1], O_RDONLY)) == -1 ){
		perror("src open"); 
		exit(1);
	} 

	// 터미널을 연다.
	if ( (dst = open(ttyname(fileno(stdin)), O_RDWR) ) == -1 ){
		perror("stdin open"); 
		exit(1);
	} 

	// read -> write 
	while ( (rcnt = read(src, buf, MAX_READ)) > 0) {
		tot_cnt += write(dst, buf, rcnt);
	}

	if (tot_cnt < 0) {
		perror("read");
		exit(1);
	} 

	close(src);
	close(dst);

}

