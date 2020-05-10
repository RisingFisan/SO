#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

int main(int argc, char const *argv[]) {
    if(argc < 3) {
        puts("WRONG NUMBER OF ARGUMENTS");
        return 1;
    }

    int BUFFER_SIZE = 100;

    if(argc == 4) {
        BUFFER_SIZE = atoi(argv[3]);
    }

    clock_t start_time = clock();

    int source = open(argv[1], O_RDONLY);
    if(source == -1) {
        printf("ERROR - %s - No such file or directory\n", argv[1]);
        exit(1);
    }

    int dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    char *buffer = malloc(BUFFER_SIZE);
    ssize_t bytesRead;

    while((bytesRead = read(source, buffer, BUFFER_SIZE)) > 0) {
        write(dest, buffer, bytesRead);
    }
    
    printf("Execution time = %lfs\n", (double)(clock() - start_time) / CLOCKS_PER_SEC);

    close(source);
    close(dest);
    return 0;
}
