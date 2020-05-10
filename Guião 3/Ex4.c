#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	char buffer[1024];
	char* args[1024];
	args[0] = "./Ex3";
	size_t i = 1;
	while(fgets(buffer, 1024, stdin)) {
		buffer[strcspn(buffer, "\n\r")] = 0;
		args[i++] = strdup(buffer);
	}
	args[i] = NULL;
	execv("./Ex3", args);
	return 0;
}
