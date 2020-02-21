#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

ssize_t readln(int fd, char* line, size_t size) {
    char* buffer = malloc(sizeof(char));
    ssize_t i = 0;
    while(i < size - 1) {
        ssize_t bytes_read = read(fd, buffer, 1);
        if(!bytes_read) break;
        line[i++] = *buffer;
        if(*buffer == '\n')
            break;
    }
    line[i] = 0;
    return i;
}

ssize_t readln2(int fd, char* line, size_t size) {
    size_t buffer_size = 1024;
    char* buffer = malloc(buffer_size * sizeof(char));
    ssize_t bytes_read = read(fd, buffer, buffer_size - 1);
    size_t line_length = strcspn(buffer, "\n") + 1;
    buffer[(line_length > size ? size : line_length)] = 0;
    strcpy(line, buffer);
    lseek(fd, line_length - bytes_read, SEEK_CUR);
    return strlen(line);
}