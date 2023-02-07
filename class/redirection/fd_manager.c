/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:15:48 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/07 01:34:59 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

void	execute_fd(t_cmd *cmd)
{
	if (cmd->heredoc_file)
	{
		call_heredoc(cmd);
		close(cmd->fd_in);
		cmd->fd_in = open(get_string(cmd->heredoc_file), O_RDONLY);
	}
	if (cmd->fd_in != STDIN_FILENO)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out != STDOUT_FILENO)
		dup2(cmd->fd_out, STDOUT_FILENO);
	close_cmd_fd(cmd);
}

void	close_fd(int fd, int std)
{
	if (fd != std)
		close(fd);
}
