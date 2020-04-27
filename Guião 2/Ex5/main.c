#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
    int status;
    for(int i = 1; i <= 10; i++) {
        pid_t pid = getpid();
        pid_t ppid = getppid();
        printf("Process %d\nPID = %d\nParentPID = %d\n\n",i,pid,ppid);
        if(fork()) {
            int terminated_pid = wait(&status);
	    printf("Process %d exited, exit code %d.\n", terminated_pid, WEXITSTATUS(status));
            _exit(i);
        }
    }
    return 0;
}
