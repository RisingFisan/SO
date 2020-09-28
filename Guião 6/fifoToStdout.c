#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[]) {
    int fd = open("/tmp/fifo", O_RDONLY);
    int bytesRead = 0;
    char buffer[1024];
    while((bytesRead = read(fd, buffer, 1024)) > 0) {
        write(STDOUT_FILENO, buffer, bytesRead);
    }
    close(fd);
    return 0;
}
