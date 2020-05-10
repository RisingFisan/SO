#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
    int pipe_fd[2];
    if(pipe(pipe_fd) < 0) {
        perror("pipe");
        exit(1);
    }

    if(fork() == 0) {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
        execlp("ls", "ls", "/etc", NULL);
        _exit(1);
    }
    else if (fork() == 0) {
        close(pipe_fd[1]);
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);
        execlp("wc", "wc", "-l", NULL);
        _exit(1);
    }
    else {
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        if (wait(NULL) == -1) puts("Error");
        if (wait(NULL) == -1) puts("Error");
    }
    return 0;
}
