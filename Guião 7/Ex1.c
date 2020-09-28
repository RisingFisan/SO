#include <signal.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

size_t ctrl_c_counter = 0;
size_t seconds = 0;

void ctrl_c_handler(int signum) {
    clock_t end = clock();
    printf("Passaram %zu segundos desde o começo do programa.\n", seconds);
    ctrl_c_counter++;
}

void ctrl_backslash_handler(int signum) {
    printf("Vezes clicadas em CTRL + C: %zu\n", ctrl_c_counter);
    exit(0);
}

void sigalrm_handler(int signum) {
    seconds++;
    alarm(1);
}

int main(int argc, char const *argv[]) {
    if(signal(SIGINT, ctrl_c_handler) == SIG_ERR) {
        puts("Erro com SIGINT");
        exit(1);
    }

    if(signal(SIGQUIT, ctrl_backslash_handler) == SIG_ERR) {
        puts("Erro com SIGQUIT");
        exit(1);
    }

    if(signal(SIGALRM, sigalrm_handler) == SIG_ERR) {
        puts("Erro com SIGALRM");
        exit(1);
    }

    alarm(1);
    while(1);
    
    return 0;
}
