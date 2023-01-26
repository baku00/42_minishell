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
#include <string.h>

typedef struct s_cmd
{
	char	*bin;
	char	**args;
	int		fd_out;
	int		redirection;
	void	*next;
	void	*prev;
}	t_cmd;

t_cmd	*create_cmd(char *bin)
{
	t_cmd	*cmd;

	cmd = calloc(sizeof(t_cmd), 1);
	cmd->bin = strdup(bin);
	cmd->args = NULL;
	cmd->fd_out = 0;
	cmd->redirection = 0;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

int	main()
{
	t_cmd *cmd = create_cmd("echo");
	t_cmd *cmd1 = create_cmd("2");
	t_cmd *cmd2 = create_cmd("4");
	t_cmd *cmd3 = create_cmd("6");
	
	char **args = calloc(sizeof(char *), 3);
	args[0] = "/bin/echo";
	args[1] = "1";
	cmd->args = args;

	char **args1 = calloc(sizeof(char *), 3);
	args1[0] = "2";
	args1[1] = "3";
	cmd1->args = args1;
	cmd->next = cmd1;
	cmd1->prev = cmd;

	char **args2 = calloc(sizeof(char *), 3);
	args2[0] = "4";
	args2[1] = "5";
	cmd2->args = args2;
	cmd1->next = cmd2;
	cmd2->prev = cmd1;

	char **args3 = calloc(sizeof(char *), 3);
	args3[0] = "6";
	args3[1] = "7";
	cmd3->args = args3;
	cmd2->next = cmd3;
	cmd3->prev = cmd2;

	cmd->fd_out = open(cmd1->bin, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	// close(cmd->fd_out);
	dup2(cmd->fd_out, STDOUT_FILENO);

	close(cmd->fd_out);
	cmd->fd_out = open(cmd2->bin, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	cmd1->fd_out = cmd->fd_out;
	dup2(cmd->fd_out, STDOUT_FILENO);

	close(cmd->fd_out);
	cmd->fd_out = open(cmd3->bin, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	cmd2->fd_out = cmd->fd_out;
	// close(cmd2->fd_out);
	dup2(cmd->fd_out, STDOUT_FILENO);
	cmd3->fd_out = cmd->fd_out;

	while (cmd)
	{
		if (cmd->prev && ((t_cmd *) cmd->prev)->fd_out != STDOUT_FILENO)
			cmd->bin = strdup(((t_cmd *)cmd->prev)->bin);
		write(cmd->fd_out, cmd->args[1], strlen(cmd->args[1]));
		if (cmd->next)
			cmd = cmd->next;
		else
			break ;
	}

	close(cmd->fd_out);
	close(cmd1->fd_out);
	close(cmd2->fd_out);
}