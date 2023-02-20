/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 01:50:44 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/17 01:10:38 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

void	free_cmd(t_cmd	*cmd)
{
	if (!cmd)
		return ;
	if (cmd->bin)
		free_string(cmd->bin);
	if (cmd->heredoc_file)
		free_string(cmd->heredoc_file);
	if (cmd->args)
		args_free_all(cmd->args);
	free(cmd);
	cmd = NULL;
}

void	*free_null_cmd(t_cmd *cmd)
{
	if (cmd)
		free_cmd(cmd);
	return (NULL);
}

void	*free_all_cmd(void *array)
{
	t_cmd	*cmd;

	if (!array)
		return (NULL);
	cmd = (t_cmd *) array;
	while (cmd->next)
	{
		cmd = cmd->next;
		free_cmd(cmd->prev);
	}
	if (cmd)
		free_cmd(cmd);
	return (NULL);
}
