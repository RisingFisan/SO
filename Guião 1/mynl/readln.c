#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

ssize_t readln(int fd, char* line, size_t size) {
    ssize_t i = 0;
    while(i < size - 1) {
        ssize_t bytes_read = read(fd, &line[i], 1);
        if(bytes_read < 1) break;
        if(line[i++] == '\n') break;
    }
    line[i] = 0;
    return i;
}

ssize_t readln2(int fd, char* line, size_t size) {
    ssize_t bytes_read = read(fd, line, size);
    if(!bytes_read) return 0;

    size_t line_length = strcspn(line, "\n") + 1;
    if(bytes_read < line_length) line_length = bytes_read;
    line[line_length] = 0;
    
    lseek(fd, line_length - bytes_read, SEEK_CUR);
    return line_length;
}