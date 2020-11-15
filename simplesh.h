#include <unistd.h>
 
int getartgs(char *cmd, char *argv[]);

#define BUF_SIZE 256
 
char buf[BUF_SIZE];
char *argv[50];
int narg, status;
pid_t pid;
char pwd[BUF_SIZE];
int BACKGROUND = 0;
