/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 19:03:52 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/26 17:19:26 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

// static int is_standart_input(int fd_in)
// {
// 	return (fd_in == STDIN_FILENO);
// }

// static int is_standart_output(int fd_out)
// {
// 	return (fd_out == STDOUT_FILENO);
// }

static int	open_file(char *path, int flags, int access_level)
{
	int	file_fd;
	int	access;

	access = check_access(path);
	if (access != IS_FILE && access != IS_NOTHING)
		return (access);
	if (access_level != -1)
		file_fd = open(path, flags, access_level);
	else
		file_fd = open(path, flags);
	if (file_fd == -1)
		return (REDIRECTION_ERROR);
	return (file_fd);
}

static int	redirect_pipe(t_cmd **cmd)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (REDIRECTION_ERROR);
	(*cmd)->fd_out = fd[1];
	((t_cmd *)(*cmd)->next)->fd_in = fd[0];
	return (1);
}

int	redirect_fd(t_cmd **cmd)
{
	t_cmd	*next;

	if (!(*cmd)->next)
		return (REDIRECTION_EMPTY);
	next = (*cmd)->next;
	if ((*cmd)->redirection_id == REDIRECTION_OUTPUT)
	{
		(*cmd)->fd_out = open_file(get_string(next->bin),
				O_WRONLY | O_TRUNC | O_CREAT, 0777);
		next->is_file = IS_FILE;
	}
	else if ((*cmd)->redirection_id == REDIRECTION_APPEND)
	{
		(*cmd)->fd_out = open_file(get_string(next->bin),
				O_WRONLY | O_APPEND | O_CREAT, 0777);
		next->is_file = IS_FILE;
	}
	else if ((*cmd)->redirection_id == REDIRECTION_INPUT)
	{
		(*cmd)->fd_in = open_file(get_string(next->bin), O_RDONLY, -1);
	}
	else if ((*cmd)->redirection_id == REDIRECTION_PIPE)
		redirect_pipe(cmd);
	return ((*cmd)->fd_in >= 0 && (*cmd)->fd_out >= 1);
}

t_args	*args_dup(t_args *prev, t_args *args)
{
	t_args	*duplicate;

	if (!args)
		return (NULL);
	duplicate = ft_calloc(sizeof(t_args), 1);
	duplicate->string = string_dup(args->string);
	duplicate->type = args->type;
	duplicate->prev = prev;
	duplicate->next = NULL;
	// printf("Args: %s\n", get_string(args->string));
	if (args->next)
		duplicate->next = args_dup(duplicate, args->next);
	return (duplicate);
}

static t_cmd *init_cmd(t_cmd *prev)
{
	t_cmd *cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (NULL);
	cmd->bin = NULL;
	cmd->args = NULL;
	cmd->type = TYPE_CMD;
	cmd->pid = 0;
	cmd->fd_in = STDIN_FILENO;
	cmd->is_file = 0;
	cmd->fd_out = STDOUT_FILENO;
	cmd->redirection_id = 0;
	cmd->info = NULL;
	cmd->next = NULL;
	cmd->prev = prev;
	return (cmd);
}

static void	append_more_args(t_args **args, t_args *append)
{
	if (!append || !args)
		return ;
	while ((*args)->next)
		*args = (*args)->next;
	(*args)->next = args_dup((*args), append);
	while ((*args)->prev)
		(*args) = (*args)->prev;
}

static void	close_cmd_fd(t_cmd *cmd)
{
	if (cmd)
	{
		if (cmd->fd_in != STDIN_FILENO)
			close (cmd->fd_in);
		if (cmd->fd_out != STDOUT_FILENO)
			close (cmd->fd_out);
	}
}

t_cmd *make_redirection(t_cmd *prev, t_cmd *cmd, int *success)
{
	t_cmd	*configured;
	int		fd[2];

	configured = init_cmd(NULL);
	if (prev)
	{
		configured->prev = prev;
		configured->fd_in = cmd->fd_in;
	}
	// printf("NEW CMD\n");
	if (cmd)
	{
		configured->bin = string_dup(cmd->bin);
		configured->args = args_dup(NULL, cmd->args);
		while (!is_redirection_pipe(cmd->redirection_id))
		{
			while (is_redirection_in(cmd->redirection_id))
			{
				if (cmd->prev && !is_redirection_pipe(((t_cmd *)cmd->prev)->redirection_id))
					close_cmd_fd(cmd->prev);
				if (!redirect_fd(&cmd))
				{
					*success = cmd->fd_in;
					return (NULL);
				}
				if (cmd->next)
					cmd = cmd->next;
				else
					break;
			}
			if (configured->fd_in == STDIN_FILENO)
			{
				configured->fd_in = cmd->fd_in;
				if (cmd->prev)
					configured->fd_in = ((t_cmd *)cmd->prev)->fd_in;
			}
			if (is_redirection_out(cmd->redirection_id))
			{
				while (is_redirection_out(cmd->redirection_id))
				{
					if (cmd->prev && is_redirection_out(((t_cmd *)cmd->prev)->redirection_id))
						close_cmd_fd(cmd->prev);
					if (!redirect_fd(&cmd))
					{
						*success = cmd->fd_out;
						return (NULL);
					}
					if (cmd->args && ((t_args *)cmd->args)->next && ((t_args *)((t_args *)cmd->args)->next)->next && cmd->prev)
					{
						// printf("Args: %s\n", get_string(((t_args *)cmd->args)->string));
						// printf("CHECK\n");
						// printf("ARGS: %s\n", get_string(((t_args *)cmd->args)->string));
						append_more_args(&configured->args, ((t_args *)((t_args *)cmd->args)->next)->next);
					}
					if (cmd->next)
						cmd = cmd->next;
					else
						break;
				}
				if (cmd->args && ((t_args *)cmd->args)->next)
					append_more_args(&configured->args, ((t_args *)cmd->args)->next);
				if (configured->fd_out == STDOUT_FILENO)
					configured->fd_out = cmd->fd_out;
				if (cmd->prev)
					configured->fd_out = ((t_cmd *)cmd->prev)->fd_out;
			}
			if (!is_redirection_in(cmd->redirection_id) && !is_redirection_out(cmd->redirection_id))
			{
				if (cmd->next)
					cmd = cmd->next;
				else
					break;
			}
		}
		if (cmd->next)
		{
			pipe(fd);
			configured->fd_out = fd[1];
			configured->redirection_id = cmd->redirection_id;
			((t_cmd *)cmd->next)->fd_in = fd[0];
			configured->next = make_redirection(configured, cmd->next, success);
		}
	}
	// if (configured->next)
	// {
		// printf("Binary: %s\n", get_string(cmd->bin));
	// 	t_cmd *next = configured->next;
	// 	while (next && next->args)
	// 	{
			// printf("Args: %s\n", get_string(((t_args *)next->args)->string));
	// 		if (((t_args *)next->args)->next)
	// 			next->args = ((t_args *)next->args)->next;
	// 		else
	// 			break;
	// 	}
	// 	while (next->args)
	// 	{
	// 		if (((t_args *)next->args)->prev)
	// 			next->args = ((t_args *)next->args)->prev;
	// 		else
	// 			break;
	// 	}
	// }
	return (configured);
}

/*
t_cmd *make_redirection(t_cmd *prev, t_cmd *cmd)
{
	t_cmd	*configured;
	int		fd[2];

	configured = init_cmd(NULL);
	if (prev)
	{
		configured->prev = prev;
		configured->fd_in = cmd->fd_in;
	}
	// printf("NEW CMD\n");
	if (cmd)
	{
		configured->bin = string_dup(cmd->bin);
		configured->args = args_dup(NULL, cmd->args);
		while (!is_redirection_pipe(cmd->redirection_id))
		{
			while (is_redirection_in(cmd->redirection_id))
			{
				if (cmd->prev && !is_redirection_pipe(((t_cmd *)cmd->prev)->redirection_id))
					close_cmd_fd(cmd->prev);
				redirect_fd(&cmd);
				if (cmd->next)
					cmd = cmd->next;
				else
					break;
			}
			if (configured->fd_in == STDIN_FILENO)
			{
				configured->fd_in = cmd->fd_in;
				if (cmd->prev)
					configured->fd_in = ((t_cmd *)cmd->prev)->fd_in;
			}
			if (is_redirection_out(cmd->redirection_id))
			{
				while (is_redirection_out(cmd->redirection_id))
				{
					if (cmd->prev && is_redirection_out(((t_cmd *)cmd->prev)->redirection_id))
						close_cmd_fd(cmd->prev);
					redirect_fd(&cmd);
					if (cmd->args && ((t_args *)cmd->args)->next && cmd->prev)
					{
						// printf("Args: %s\n", get_string(((t_args *)cmd->args)->string));
						// printf("CHECK\n");
						// printf("ARGS: %s\n", get_string(((t_args *)cmd->args)->string));
						append_more_args(&configured->args, ((t_args *)cmd->args)->next);
					}
					if (cmd->next)
						cmd = cmd->next;
					else
						break;
				}
				if (cmd->args && ((t_args *)cmd->args)->next)
					append_more_args(&configured->args, ((t_args *)cmd->args)->next);
				if (configured->fd_out == STDOUT_FILENO)
					configured->fd_out = cmd->fd_out;
				if (cmd->prev)
					configured->fd_out = ((t_cmd *)cmd->prev)->fd_out;
			}
			if (!is_redirection_in(cmd->redirection_id) && !is_redirection_out(cmd->redirection_id))
			{
				if (cmd->next)
					cmd = cmd->next;
				else
					break;
			}
		}
		if (cmd->next)
		{
			pipe(fd);
			configured->fd_out = fd[1];
			configured->redirection_id = cmd->redirection_id;
			((t_cmd *)cmd->next)->fd_in = fd[0];
			configured->next = make_redirection(configured, cmd->next);
		}
	}
	// if (configured->next)
	// {
		// printf("Binary: %s\n", get_string(cmd->bin));
	// 	t_cmd *next = configured->next;
	// 	while (next && next->args)
	// 	{
			// printf("Args: %s\n", get_string(((t_args *)next->args)->string));
	// 		if (((t_args *)next->args)->next)
	// 			next->args = ((t_args *)next->args)->next;
	// 		else
	// 			break;
	// 	}
	// 	while (next->args)
	// 	{
	// 		if (((t_args *)next->args)->prev)
	// 			next->args = ((t_args *)next->args)->prev;
	// 		else
	// 			break;
	// 	}
	// }
	return (configured);
}
*/