#ifndef READLN_H
#define READLN_H

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

ssize_t readln(int fd, char* line, size_t size);
ssize_t readln2(int fd, char* line, size_t size);

#endif