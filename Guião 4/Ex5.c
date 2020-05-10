#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

ssize_t readline(int fd, char* buf, int size);

int main(int argc, char const *argv[]) {
    char* buffer = calloc(1024, sizeof(char));
    char* args[1024];
    size_t len = 0;
    size_t back_n = 0;

    int stdin_backup = dup(STDIN_FILENO);
    int stdout_backup = dup(STDOUT_FILENO);
    int stderr_backup = dup(STDERR_FILENO);

    while((len = readline(STDIN_FILENO, buffer, 1024)) > 0) {
        size_t i = 0;
        char* token;
        while((token = strtok_r(buffer, " ", &buffer))) {
            args[i] = strdup(token);
            if(i > 1) {
                if(strcmp(args[i-1],">") == 0) {
                    int fd = open(args[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                    i-=2;
                }
                else if(strcmp(args[i-1],">>") == 0) {
                    int fd = open(args[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                    i-=2;
                }
                else if(strcmp(args[i-1],"<") == 0) {
                    int fd = open(args[i], O_RDONLY);
                    dup2(fd, STDIN_FILENO);
                    close(fd);
                    i-=2;
                }
                else if(strcmp(args[i-1],"2>") == 0) {
                    int fd = open(args[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    dup2(fd, STDERR_FILENO);
                    close(fd);
                    i-=2;
                }
                else if(strcmp(args[i-1],"2>>") == 0) {
                    int fd = open(args[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
                    dup2(fd, STDERR_FILENO);
                    close(fd);
                    i-=2;
                }
            }
            i++;
        }
        int background = 0;
        if(strcmp(args[0], "exit") == 0) {
            break;
        }
        if(strcmp(args[i-1], "&") == 0) {
            background = 1;
            i--;
        }
        args[i] = NULL;

        int pid;
        if(!(pid = fork())) {
            execvp(args[0], args);
            _exit(1);
        }
        else {
            if(!background) waitpid(pid, NULL, 0);
            else back_n++;
        }

        dup2(stdin_backup, STDIN_FILENO);
        dup2(stdout_backup, STDOUT_FILENO);
        dup2(stderr_backup, STDERR_FILENO);
    }

    for(size_t i = 0; i < back_n; i++) wait(NULL);

    close(stdin_backup);
    close(stdout_backup);
    close(stderr_backup);
    
    return 0;
}

ssize_t readline(int fd, char* buf, int size) {
    ssize_t bytesRead = read(fd, buf, size);
    if(!bytesRead) return 0;

    size_t len = strcspn(buf,"\n");
    if(bytesRead < len) len = bytesRead;
    buf[len] = 0;

    lseek(fd, len - bytesRead, SEEK_CUR);
    return len;
}