/*5. Now write a program that uses wait() to wait for the child process
to finish in the parent. What does wait() return? What happens if
you use wait() in the child?*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
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
		printf("child here %d\n", getpid());
	}else{
		printf("parent here %d\n", getpid());
		x=wait(NULL);									//x gets the child pid, the process the parent waited for
		printf("parent done, return code: &d\n", ); 
	}
	return 0;
}