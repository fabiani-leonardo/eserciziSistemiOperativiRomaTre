/*Write another program using fork(). The child process should
print “hello”; the parent process should print “goodbye”. You should
try to ensure that the child process always prints first; can you do
this without calling wait() in the parent?
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	pid_t pid=fork();
	if (pid<0){
		return -1;
	}
	if (pid==0){
		printf("hello\n");
        //fflush(stdout); // Ensure the output is flushed immediately
	}
	else{
		wait(NULL);
		//usleep(100); // Slight delay to ensure the child executes first
		printf("goodbye\n");
		
	}
	return 0;
}