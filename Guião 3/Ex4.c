#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	char buffer[1024];
	puts("Number of elements:");
	fgets(buffer, 1024, stdin);
	long N = strtod(buffer, NULL);
	char* args[N+2];
	args[0] = "./Ex3";
	for(size_t i = 1; i <= N; i++) {
		fgets(buffer, 1024, stdin);
		buffer[strcspn(buffer, "\n\r")] = 0;
		args[i] = strdup(buffer);
	}
	args[N+1] = NULL;
	execv("./Ex3", args);
	return 0;
}
