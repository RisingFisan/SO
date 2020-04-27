#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
    int pipe_fd[2];
    if(pipe(pipe_fd) < 0) {
        perror("pipe");
        exit(1);
    }

    int pid;
    if((pid = fork()) == 0) {
        close(pipe_fd[1]);
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);
        execlp("wc","wc",NULL);
    } else {
        close(pipe_fd[0]);
        int bytes;
        char buf[10];
        while((bytes = read(STDIN_FILENO, buf, 10)) > 0)
            write(pipe_fd[1], buf, bytes);
        close(pipe_fd[1]);
        wait(NULL);
    }
    return 0;
}