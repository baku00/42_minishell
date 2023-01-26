#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <termios.h>
#include <signal.h>

int main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;
	if (argc == 0)
		return (0);
	char *bin = "/bin/cat";
	char *args[] = {"/bin/cat", "test", "test2", "test3", "test4", NULL};
	char *input = "free.c";
	int fd = open(input, O_RDONLY);
	int pid = fork();
	if (pid == 0)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
		if (execve(bin, args, envp) == 0)
		{
			printf("Success");
		}
		perror("Error:");
		exit(127);
	}
	int status = 0;
	waitpid(pid, &status, 0);
	close(fd);
	return (0);
}