#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define ROWS 10
#define COLUMNS 10000

int main(void) {
	srand((int)time(NULL));
	int matrix[ROWS][COLUMNS];
	puts("Generating random matrix...");
	for(size_t i = 0; i < ROWS; i++)
		for(size_t j = 0; j < COLUMNS; j++)
			matrix[i][j] = rand() % COLUMNS;

	int pid;
	int num = rand() % COLUMNS;
	for(size_t i = 0; i < ROWS; i++) {
		if((pid = fork()) == 0) {
			// procura na linha
			for(size_t j = 0; j < COLUMNS; j++) {
				if(matrix[i][j] == num)
					_exit(1);	
			}
			_exit(0);
		}
	}

	int ocurrences = 0;
	int status;
	for(size_t i = 0; i < ROWS; i++) {
		int pid = wait(&status);
		if(WEXITSTATUS(status) == 1)
			ocurrences++;
	}

	printf("%d ocurrences of %d were found.\n", ocurrences, num);

	return 0;
}
