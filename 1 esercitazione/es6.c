/*6. Write a slight modification of the previous program, this time using waitpid() instead of wait(). When would waitpid() be
useful?*/

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
		usleep(2000000);
		printf("childe done\n");

	}else{
		printf("parent here %d\n", getpid());
		waitpid(pid,NULL,0);					//WAITPID, pid è il pid del figlio, NULL è &status che restituisce il figlio, 0 rappresenta nessuna flag usata
		printf("parent, done");
	}
	return 0;
}