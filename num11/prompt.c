#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_PATH 100
//#define LF 10

int print_prompt()
{
	char *buffer = (char *)malloc( sizeof(char) * MAX_PATH); 
	char *value = getcwd (buffer, MAX_PATH); 

	if (value != NULL)	
		fprintf(stdout,"minish:%s>",buffer);
	
	free (buffer); 
	
	return 0;
}
/*
int main()
{
	char c;
	
	while((c=getchar())!=EOF)		
		if(c==LF)	
			print_prompt();

	return 0;
}*/
