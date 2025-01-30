/*7. Write a program that creates a child process, and then in the child
closes standard output (STDOUT FILENO). What happens if the child
calls printf() to print some output after closing the descriptor?*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	pid_t pid=fork();
	if (pid<0)
	{
		return -1;
	}
	if (pid==0)
	{
		// Child process
        printf("Child: This will be printed before closing STDOUT_FILENO.\n");
        
        // Close standard output
        close(STDOUT_FILENO);

        // Attempt to print after closing standard output
        printf("Child: This message will not appear because STDOUT_FILENO is closed.\n");
        fflush(stdout);

        // Exit the child process
        exit(0);
	}else{
		printf("parent here waiting for child\n");
		wait(NULL);
		printf("parent closing\n");
		exit(0);
	}
	return 0;
}