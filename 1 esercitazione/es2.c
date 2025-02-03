/*2. Write a program that opens a file (with the open() system call)
and then calls fork() to create a new process. Can both the child
and parent access the file descriptor returned by open()? What
happens when they are writing to the file concurrently, i.e., at the
same time?
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{

	int fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644); 	//Indica che il file deve essere creato se non esiste già. 														O_CREAT
																		//Specifica che il file deve essere aperto in modalità scrittura (write-only). Non è possibile leggerlo. 		O_WRONLY
																		//Se il file esiste già, il suo contenuto verrà troncato (cioè svuotato) a lunghezza zero. 						O_TRUNC
																		//Questo parametro specifica i permessi del file, ma è usato solo se il file viene creato (grazie a O_CREAT) 	0644
    if (fd < 0) {
        perror("Errore nell'apertura del file");
        return 1;
    }

	pid_t pid=fork();
	if (pid<0)
	{	
		return -1;
	}
	if (pid==0)
	{
		const char *child_msg = "Messaggio dal figlio\n";
        for (int i = 0; i < 10000; i++) {
            write(fd, child_msg, sizeof("Messaggio dal figlio\n") - 1);
        }
	}
	else{
		const char *parent_msg = "Messaggio dal genitore\n";
        for (int i = 0; i < 10000; i++) {
            write(fd, parent_msg, sizeof("Messaggio dal genitore\n") - 1);
        }
	}
	close(fd);
	return 0;
}