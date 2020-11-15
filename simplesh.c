/* simplesh.c */
#include "simplesh.h"
#include "header.h"
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
   char buf[256];
   char *argv[50];
   int narg;   
   pid_t pid;
    
    while (1) {
        getcwd(pwd,BUF_SIZE);
        printf("%s$ ", pwd);
        gets(buf);
        narg = getargs(buf, argv);
     
        sig_int();
        sig_quit();
 
        pid = fork();
        
        if (pid == 0)
           if(strcmp(argv[0],"cd"))
            if(!BACKGROUND){
             if(execvp(argv[0], argv) == -1)
               printf("%s: wrong command\n",argv[0]);
             else{
               printf("process is background\n");
               execvp(argv[0], argv);
                }
               exit(1);
             }
        else if (pid > 0){
           if(!BACKGROUND)
               pid = wait(&status);
              }
        else
            perror("fork failed");
          }
   }
 int getargs(char *cmd, char **argv)
 {
     int narg = 0;
     while (*cmd) {
             if (*cmd == ' ' || *cmd == '\t' || *cmd == '&')
             *cmd++ = '\0';
 
           // 명령의 마지막에 & 문자를 입력할 경우 백그라운드로 실행
          if (*cmd == '&')
             BACKGROUND = 1;
 
        else {
              argv[narg++] = cmd++;
                while (*cmd != '\0' && *cmd != ' ' && *cmd != '\t')
                  cmd++;
        }
   }
    
     if(strcmp("exit", argv[0]) == 0){ 
     printf("\n SHELL EXIT \n");
     exit(1);
     } // EXIT  
  
     if(strcmp("cd", argv[0]) == 0){
     file_chdir(narg, argv);
     } // cd
 
    argv[narg] = NULL;
    return narg;
 }
