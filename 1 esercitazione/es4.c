/*Write a program that calls fork() and then calls some form of
exec() to run the program /bin/ls. See if you can try all of the
variants of exec(), including (on Linux) execl(), execle(),
execlp(), execv(), execvp(), and execvpe(). Why do
you think there are so many variants of the same basic call?*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    pid_t pid = fork();

    if (pid < 0) {
        return -1;
    }
    if (pid == 0) {
        printf("I am the child and running /bin/ls with exec... %d\n", getpid());
        execl("/bin/ls", "ls", (char *)NULL);										//EXECL richiede almeno 3 argomenti: percorso, nome, (char *)NULL
    } else {
        printf("Parent here, waiting for child to finish %d\n", getpid());
        wait(NULL);
        printf("Parent done\n");
    }
    return 0;
}
