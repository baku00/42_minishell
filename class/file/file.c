/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 01:38:02 by my_name_          #+#    #+#             */
/*   Updated: 2023/03/06 00:55:11 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

void	close_cmd_fd(t_cmd *cmd)
{
	if (cmd)
	{
		if (cmd->fd_in != STDIN_FILENO)
			close (cmd->fd_in);
		if (cmd->fd_out != STDOUT_FILENO)
			close (cmd->fd_out);
	}
}

void	close_all_fd(t_cmd *cmd)
{
	while (cmd)
	{
		close_cmd_fd(cmd);
		if (cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
}

void	copy_fd_in_and_out(t_cmd **configured, t_cmd *cmd)
{
	if ((*configured)->fd_in == STDIN_FILENO)
		(*configured)->fd_in = cmd->fd_in;
	if ((*configured)->fd_out == STDOUT_FILENO)
		(*configured)->fd_out = cmd->fd_out;
}

int	has_permission(char *path, int flags)
{
	int	write;
	int	read;
	int	append;
	int	error;

	write = O_WRONLY | O_TRUNC | O_CREAT;
	read = O_RDONLY;
	append = O_WRONLY | O_APPEND | O_CREAT;
	error = 0;
	if ((flags == write || flags == append) && access(path, W_OK))
		error = 1;
	else if (flags == read && access(path, R_OK))
		error = 1;
	return (error);
}

int	open_file(char *path, int flags, int access_level)
{
	int	file_fd;
	int	has_access;

	has_access = check_access(path);
	if (has_permission(path, flags) && has_access == IS_FILE)
	{
		g_status = 126;
		return (PREMISSION_NOT_FOUND);
	}
	if (has_access != IS_FILE && has_access != IS_NOTHING)
		return (has_access);
	if (access_level != -1)
		file_fd = open(path, flags, access_level);
	else
		file_fd = open(path, flags);
	if (file_fd == -1)
		return (REDIRECTION_ERROR);
	return (file_fd);
}
