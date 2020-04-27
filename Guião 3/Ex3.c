#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char* argv[]) {
	for(size_t i = 0; i < argc; i++) {
		puts(argv[i]);
	}
	return 0;
}
