/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 23:23:26 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/21 02:14:44 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

t_cmd	*init_cmd(t_cmd *prev)
{
	t_cmd	*cmd;

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
	cmd->error_id = 0;
	cmd->redirection_id = 0;
	cmd->heredoc = NULL;
	cmd->info = NULL;
	cmd->next = NULL;
	cmd->prev = prev;
	if (prev)
		prev->next = cmd;
	return (cmd);
}
