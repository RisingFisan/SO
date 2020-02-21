#include <stdio.h>
#include <string.h>
#include <time.h>
#include "readln.h"

typedef ssize_t (*funcs[2])(int fd, char* line, size_t size);
funcs readlns = {readln, readln2};

int main(int argc, char const *argv[]) {

    char line[1024];
    int file = open(argv[1], O_RDONLY);

    int mode = 1;
    if(argc > 2) {
        mode = atoi(argv[2]) - 1;
    }

    size_t size;

    clock_t start = clock();
    
    int i = 0;
    while((size = readlns[mode](file, line, 1024))) {
        char lineno[100];
        sprintf(lineno, "%*d  ", 6, i++);
        write(STDOUT_FILENO, lineno, strlen(lineno));
        write(STDOUT_FILENO, line, size);
    }

    printf("\n\nExecution time (mode %d) = %lf s\n", (mode + 1), (double)(clock() - start) / CLOCKS_PER_SEC);

    close(file);
    return 0;
}