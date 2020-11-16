CFLAG=-g -Wall -Wextra

minish : libstatic.a
	gcc -I./ -o minish ${CFLAG} simplesh.c -L./ -lstatic

libstatic.a : prompt.o parsing.o command.o execute.o demon.o signalhandler.o
	ar rcs libstatic.a prompt.o parsing.o command.o execute.o demon.o signalhandler.o

prompt.o : prompt.c
	gcc -c prompt.c

command.o : command.c
	gcc -c command.c

execute.o : execute.c
	gcc -c execute.c

demon.o : demon.c
	gcc -c demon.c

signalhandler.o : signalhandler.c
	gcc -c signalhandler.c

clean :
	rm -f libstatic.a prompt.o parsing.o command.o execute.o demon.o signalhandler.o
	rm -f minish	

