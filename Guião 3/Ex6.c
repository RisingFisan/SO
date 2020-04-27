#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define N 1024

int my_system(char* command) {
	char* args[N];
	char* token;
	char* rest = command;
	size_t i = 0;
	while((token = strtok_r(rest, " ", &rest)))
		args[i++] = strdup(token);
	args[i] = NULL;

	if(fork() == 0) {
		int exec_ret = execvp(args[0], args);
		_exit(exec_ret);
	}
}

int main(int argc, const char * argv[]) {
	char buffer[N];
	puts("Insert a command:");
	fgets(buffer, N, stdin);
	buffer[strcspn(buffer, "\n\r")] = 0;
	int ret = my_system(buffer);
	return 0;
}
