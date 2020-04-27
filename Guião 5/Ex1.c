#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
    int pipe_fd[2];
    if(pipe(pipe_fd) < 0) {
        perror("pipe");
        exit(1);
    }
    // criar processo-filho.
    int pid = -1;
    if((pid = fork()) == 0) {
        // Herda descritores do pipe.
        // Fechamos descritores que não serão utilizados no processo-filho.
        close(pipe_fd[1]);
        //Temos extremidade de leitura do pipe.
        char buf[10];
        // puts("Esperando...");
        int bytes = read(pipe_fd[0], buf, 10);

        printf("li %d bytes: %s\n", bytes, buf);
        _exit(0);
    } else {
        close(pipe_fd[0]);

        // Temos extremidade de escrita do pipe.
        char * str = "teste";
        // sleep(5);
        write(pipe_fd[1], str, strlen(str) + 1);
        // comunicação pai -> filho
        wait(NULL);
    }

    return 0;
}
