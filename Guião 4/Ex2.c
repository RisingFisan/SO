#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, const char * argv[]) {
	int input_fd = open("/etc/passwd", O_RDONLY);

	int output_fd = open("saida.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	int error_fd = creat("erros.txt", 0644);

	int stdin_fd_backup = dup(STDIN_FILENO);
	int stdout_fd_backup = dup(STDOUT_FILENO);
	int stderr_fd_backup = dup(STDERR_FILENO);

	int stdin_fd = dup2(input_fd, STDIN_FILENO);
	int stdout_fd = dup2(output_fd, STDOUT_FILENO);
	int stderr_fd = dup2(error_fd, STDERR_FILENO);
	
	close(input_fd);
	close(output_fd);
	close(error_fd);

	pid_t pid = -1;

	if((pid = fork()) == 0) {
		char buffer[10];
		int bytes = 0;

		while((bytes = read(STDIN_FILENO, &buffer, 10)) > 0) {
			write(STDOUT_FILENO, &buffer, bytes);
			write(STDERR_FILENO, &buffer, bytes);
		}
	}
	else {
		wait(NULL);

		dup2(stdin_fd_backup, STDIN_FILENO);
		dup2(stdout_fd_backup, STDOUT_FILENO);
		dup2(stderr_fd_backup, STDERR_FILENO);

		close(stdin_fd_backup);
		close(stdout_fd_backup);
		close(stderr_fd_backup);

		char str[] = "Operação concluída com sucesso.\n";
		write(STDOUT_FILENO, str, strlen(str) + 1);
	}

	return 0;
}
