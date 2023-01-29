/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 01:38:02 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/28 02:16:46 by my_name_         ###   ########.fr       */
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

int	open_file(char *path, int flags, int access_level)
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
