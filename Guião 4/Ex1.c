#include <unistd.h>
#include <fcntl.h>

int main(int argc, const char * argv[]) {
	int input_fd = open("/etc/passwd", O_RDONLY);

	int output_fd = open("saida.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	int error_fd = creat("erros.txt", 0644);

	int stdin_fd = dup2(input_fd, STDIN_FILENO);
	int stdout_fd = dup2(output_fd, STDOUT_FILENO);
	int stderr_fd = dup2(error_fd, STDERR_FILENO);
	
	close(input_fd);
	close(output_fd);
	close(error_fd);

	char buffer[10];
	int bytes = 0;
	while((bytes = read(STDIN_FILENO, &buffer, 10)) > 0) {
		write(STDOUT_FILENO, &buffer, bytes);
		write(STDERR_FILENO, &buffer, bytes);
	}

	return 0;
}
