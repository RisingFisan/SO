#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
    int pipe_fd[2][2];
    if(pipe(pipe_fd[0]) < 0) {
        perror("pipe");
        exit(1);
    }

    if(fork() == 0) {
        close(pipe_fd[0][0]);
        dup2(pipe_fd[0][1], STDOUT_FILENO);
        close(pipe_fd[0][1]);
        execlp("grep", "grep", "-v", "^#", "/etc/passwd", NULL);
        _exit(1);
    }
    
    close(pipe_fd[0][1]);

    if(pipe(pipe_fd[1]) < 0) {
        perror("pipe");
        exit(1);
    }
    
    if (fork() == 0) {
        close(pipe_fd[1][0]);

        dup2(pipe_fd[0][0], STDIN_FILENO);
        close(pipe_fd[0][0]);
        dup2(pipe_fd[1][1], STDOUT_FILENO);
        close(pipe_fd[1][1]);
        execlp("cut", "cut", "-f7", "-d:", NULL);
        _exit(1);
    }
    
    close(pipe_fd[0][0]);
    close(pipe_fd[1][1]);

    if(pipe(pipe_fd[2]) < 0) {
        perror("pipe");
        exit(1);
    }
    
    if (fork() == 0) {
        close(pipe_fd[2][0]);

        dup2(pipe_fd[1][0], STDIN_FILENO);
        close(pipe_fd[1][0]);
        dup2(pipe_fd[2][1], STDOUT_FILENO);
        close(pipe_fd[2][1]);
        execlp("uniq", "uniq", NULL);
        _exit(1);
    }

    close(pipe_fd[1][0]);
    close(pipe_fd[2][1]);

    if (fork() == 0) {
        dup2(pipe_fd[2][0], STDIN_FILENO);
        close(pipe_fd[2][0]);
        execlp("wc", "wc", "-l", NULL);
        _exit(1);
    }

    close(pipe_fd[2][0]);

    if (wait(NULL) == -1) puts("Error");
    if (wait(NULL) == -1) puts("Error");
    if (wait(NULL) == -1) puts("Error");
    if (wait(NULL) == -1) puts("Error");
    
    return 0;
}
