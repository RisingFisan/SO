#include <unistd.h>
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
    while((len = readline(STDIN_FILENO, buffer, 1024)) > 0) {
        size_t i = 0;
        char* token;
        while((token = strtok_r(buffer, " ", &buffer))) {
            args[i++] = strdup(token);
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
        }
        else {
            if(!background) waitpid(pid, NULL, 0);
            else back_n++;
        }
    }
    for(size_t i = 0; i < back_n; i++) wait(NULL);
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