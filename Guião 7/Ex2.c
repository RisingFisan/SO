#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

// grep <palavra> <file> ...
// multigrep <palavra> <file> ...

//Exit status:
// 0 -> found
// 1 -> not found
// >1 -> error

int main(int argc, char const *argv[]) {
    if(argc < 3) {
        puts("Usage: multigrep <palavra> <file> ...");
        return 5;
    }

    int files_count = argc - 2;
    // argv = ['multigrep', 'palavra', 'file1', 'file2', NULL];
    // files = ['file1', 'file2', NULL];

    const char ** files = argv + 2;
    int pids[files_count];

    for(int i = 0; i < files_count; i++) {
        pid_t pid = -1;
        if((pid = fork()) == 0) {
            printf("grep #%d with pid %d for file %s\n", i, getpid(), files[i]);

            if(execlp("grep", "grep", argv[1], files[i], NULL) < 0) {
                perror("exec grep");
                exit(10);
            }
        }
        pids[i] = pid;
    }
        
    int status = 0;
    int found = 0;
    int pid;
    while(!found && (pid = wait(&status)) > 0) {
        if(WIFEXITED(status)) {
            switch (WEXITSTATUS(status)) {
            case 0:
                // grep found the word.
                found = 1;
                printf("grep with pid %d found the word.\n", pid);
                break;
            default:
                // grep did not find the word.
                printf("grep with pid %d did not find the word.\n", pid);
                break;
            }
        }
    }

    if(!found)
        return 1;

    for(int i = 0; i < files_count; i++) {
        printf("Trying to kill grep with pid %d\n", pids[i]);
        if(pid != pids[i] && pids[i] > 0) {
            kill(pids[i], SIGKILL);

            if(waitpid(pids[i], &status, 0) > 0) {
                if(WIFEXITED(status)) {
                    printf("grep %d finished.\n", pids[i]);
                }
                else {
                    printf("grep %d was killed.\n", pids[i]);
                }
            }
        }
    }

    return 0;
}
