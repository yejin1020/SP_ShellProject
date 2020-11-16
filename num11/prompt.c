#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_PATH 100

/////////////////////////////////////////////////
// 현재 디렉토리를 알려주는 프롬프트 
/////////////////////////////////////////////////
int print_prompt()
{
	char *buffer = (char *)malloc( sizeof(char) * MAX_PATH); 
	char *value = getcwd (buffer, MAX_PATH); 

	if (value != NULL)	
		fprintf(stdout,"minish:%s>",buffer);
	
	free (buffer); 
	
	return 0;
}
