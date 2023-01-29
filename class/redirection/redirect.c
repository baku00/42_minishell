/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 19:03:52 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/28 20:31:50 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

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
	else if ((*cmd)->redirection_id == REDIRECTION_HEREDOC)
	{
		(*cmd)->fd_in = open_file(get_string(next->bin),
				O_RDWR | O_TRUNC | O_CREAT, 0777);
		next->is_file = IS_FILE;
	}
	else if ((*cmd)->redirection_id == REDIRECTION_PIPE)
		redirect_pipe(cmd);
	return ((*cmd)->fd_in >= 0 && (*cmd)->fd_out >= 1);
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

t_cmd	*make_redirection(t_cmd *prev, t_cmd *cmd, int *success)
{
	t_cmd	*configured;
	int		fd[2];

	configured = init_cmd(NULL);
	if (prev)
	{
		configured->prev = prev;
		configured->fd_in = cmd->fd_in;
	}
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
					break ;
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
						append_more_args(&configured->args, ((t_args *)((t_args *)cmd->args)->next)->next);
					if (cmd->next)
						cmd = cmd->next;
					else
						break ;
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
					break ;
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
	return (configured);
}
