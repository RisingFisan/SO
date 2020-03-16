#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
    pid_t pid;
    if((pid = fork()) == 0) {
        pid_t childPID = getpid();
        pid_t childPPID = getppid();
        printf("Child PID = %d\nChild PPID = %d\n", childPID, childPPID);
    }
    else {
        pid_t parentPID = getpid();
        pid_t parentPPID = getppid();
        pid_t parentChildPID = pid;
        printf("Parent PID = %d\nParent PPID = %d\nChild PID from Parent = %d\n\n", parentPID, parentPPID, parentChildPID);
        wait(NULL);
    }
    return 0;
}