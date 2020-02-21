#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

int main(int argc, char const *argv[]) {
    char buffer[1024];
    ssize_t bytes_read = 0;

    while(bytes_read = read(0,buffer,1024)){
        write(STDOUT_FILENO, buffer, bytes_read);
    }
    return 0;
}
