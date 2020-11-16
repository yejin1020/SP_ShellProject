#include "header.h"

void file_chdir(int narg, char *argv[]){
  if(narg > 2){
     printf("Too many arguments\n");
  }
  
  if(narg == 2){
     if(chdir(argv[1]) == 0);
     else perror(NULL);
  }
}
