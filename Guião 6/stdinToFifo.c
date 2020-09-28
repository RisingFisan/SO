#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[]) {
    char buffer[1024];
    int bytesRead = 0;
    int fd = open("/tmp/fifo", O_WRONLY);
    while((bytesRead = read(STDIN_FILENO, buffer, 1024)) > 0) {
        write(fd, buffer, bytesRead);
    }
    close(fd);
    return 0;
}
