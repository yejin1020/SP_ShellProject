#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <syslog.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void demon(char *cmd)
{
	int i, fd0, fd1, fd2;
	pid_t pid;
	struct rlimit rl;
	struct sigaction sa;

	umask(0) ; /* clear out file creation mask */

	if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
		perror("getrlimit");

	if ((pid = fork()) < 0);
	else if (pid != 0)
		exit(1) ; /* The parent process exits */

	setsid() ; /* become session leader */

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	if (sigaction(SIGHUP, &sa, NULL) < 0)
		perror("sigaction: can't ignore SIGHUP");

	chdir("/") ; /* change the working dir */

	if (rl.rlim_max == RLIM_INFINITY)
		rl.rlim_max = 1024;
	for (i = 0; i < rl.rlim_max; i++)
		close(i);

	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0); fd2 = dup(0);

	openlog(cmd, LOG_CONS, LOG_DAEMON);

	if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
		syslog(LOG_ERR,	"unexpected descriptors %d %d %d", fd0, fd1, fd2);
	exit(1);
	}

	syslog(LOG_INFO, "This is daemon test process\n\n\n");
}

