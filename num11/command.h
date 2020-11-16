#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <syslog.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>

int print_prompt();
int getargs(char *cmd, char **argv);
int shellcmd(int argc, char *argv[]);
void cmd_cd(int argc, char *argv[]);
void cmd_exit();
void cmd_pwd();
void cmd_ls(int argc, char *argv[]);
void cmd_cp(int argc, char *argv[]);
void cmd_rm(int argc, char *argv[]);
void cmd_ln(int argc, char *argv[]);
void cmd_mv(int argc, char *argv[]);
void cmd_mkdir(int argc, char *argv[]);
void cmd_rmdir(int argc, char *argv[]);
void cmd_cat(int argc, char *argv[]);
void execute(int argc, char *argv[]);
void demon(char *cmd);
//void handler_int(int signo);
//void handler_quit(int signo);
void signal_int();
void signal_quit();
void blocksignal();
