#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
    for(int i = 1; i < 11; i++) {
        if(fork() == 0) {
            pid_t PID = getpid();
            pid_t PPID = getppid();
            printf("Child PID = %d\nChild's parent PID = %d\n", PID, PPID);
            _exit(i);
        }
        int exit_status;
        wait(&exit_status);
        printf("%d\n",WEXITSTATUS(exit_status));
    }
    return 0;
}
