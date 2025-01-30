#include <stdlib.h>
#include <unistd.h> //necessaria per fork() e pid
#include <stdio.h>


int main(int argc, char const *argv[])
{
	int x=100;
	pid_t pid = fork();	

	if (pid<0){		//errore
		return -1;
	}
	if (pid==0)		//child è 0
	{
		printf("child value=%d\n", x);
		x=200;
		printf("new child value=%d\n",x);
	}else{			//il parent ha un valore di pid sicuramente diverso da 0
		printf("parent value=%d\n", x);
		x=500;
		printf("new parent value=%d\n",x);
	}


	return 0;		//da notare che entrambi i processi sono uguali alla chiamata della fork ed il precedente spazio di memoria è stato copiato nel child, quindi x avrrà lo stesso valore iniziale
}