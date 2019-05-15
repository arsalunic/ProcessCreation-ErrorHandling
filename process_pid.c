#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
/* 	create a child process running a new program
	program = name of the program to run
	arg_list = argument list, a NULL-terminated list of character strings   
 */
void create (char* program, char** arg_list){	pid_t child_pid; 	child_pid = fork();	if(child_pid < 0){		fprintf(stderr, "fork failed...\n");
		exit(1);
	}else if(child_pid == 0){		//printf("I am a child process with process id of: %d \n", (int)child_pid); //execl("ls", "-l", "/", NULL); -- exec has to call arg_list		execvp(program, arg_list); //executing program using exec family...
		printf("*** %s\n", strerror(errno)); //prints appropriate error msg...		abort();
	}else{
		//printf("I am a parent of Child process id: %d with parent id of %d\n", (int)child_pid, (int)getpid()); //parent returns 0 to go into child block that runs the program.
	}
}
int main (){
	/* argument list for the "ls" command.  */
	char* arg_list[] = {
			"ls",     /* argv[0], the name of the program  */
			"-l",
			"/",
			NULL      /* The argument list must end with a NULL.  */
	};
	/* create a child process running the "ls" command  */
	create ("ls", arg_list);

	sleep(10); /* sleep 10 seconds */
	create ("doSomethingInvalid", NULL);
	sleep(10); /* sleep 10 seconds */
	printf ("Normal main program termination\n");
	return 0;
}
