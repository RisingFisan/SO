#include <stdio.h>
#include <unistd.h>     /*chamadas ao sistema: defs e decls essenciais*/
#include <sys/wait.h>   /*chamadas wait*() e macros relacionadas*/

int main(int argc, char const *argv[]) {
    pid_t pid = getpid();
    pid_t ppid = getppid();
    printf("The PID is %d.\nThe PPID is %d.\n",(int)pid,(int)ppid);
    return 0;
}
