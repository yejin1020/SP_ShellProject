/* handlesignal.c */  

#include "header.h"
#include <signal.h>

void handler_int(int signo){
    printf("\nSIGINT START\n");
    pid_t ppid = getppid();
    kill(ppid, SIGINT);
}

void handler_quit(int signo){
    printf("\nSIGQUIT START\n");
    pid_t ppid = getppid();
    kill(ppid, SIGQUIT);
}

void sig_int(){
    struct sigaction sig_int;
    sig_int.sa_handler = handler_int; 
    sigfillset(&(sig_int.sa_mask)); 
    sigaction(SIGINT, &sig_int, NULL);
}

void sig_quit(){
    struct sigaction sig_quit;
    sig_quit.sa_handler = handler_quit;
    sigfillset(&(sig_quit.sa_mask));
    sigaction(SIGTSTP, &sig_quit, NULL);
}
