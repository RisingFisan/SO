#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
    for(int i = 1; i < 11; i++) {
        pid_t pid = getpid();
        pid_t ppid = getppid();
        printf("PID = %d\nParentPID = %d\n\n",pid,ppid);
        if(fork()) {
            wait(NULL);
            break;
        }
    }
    return 0;
}
