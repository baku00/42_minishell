/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 01:50:44 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/21 02:52:35 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

void	free_heredoc(t_heredoc *heredoc)
{
	if (!heredoc)
		return ;
	free_string(heredoc->file);
	if (heredoc->next)
		free_heredoc(heredoc->next);
	free(heredoc);
	heredoc = NULL;
}

void	free_cmd(t_cmd	*cmd)
{
	if (!cmd)
		return ;
	if (cmd->bin)
		free_string(cmd->bin);
	if (cmd->heredoc)
		free_heredoc(cmd->heredoc);
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
