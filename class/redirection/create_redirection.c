/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:44:43 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/13 23:09:38 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

int	create_redirection_pipe(t_cmd **configured, t_cmd **cmd)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		ft_putendl_fd("Erreur sur l'initialisation d'un pipe", STDERR_FILENO);
		return (0);
	}
	(*configured)->fd_out = fd[1];
	(*configured)->redirection_id = (*cmd)->redirection_id;
	((t_cmd *)(*cmd)->next)->fd_in = fd[0];
	return (1);
}

int	create_redirection(t_cmd **configured, t_cmd **cmd, int *success)
{
	int	prev_r_id;

	while (is_redirection_in_or_out((*cmd)->redirection_id))
	{
		if ((*cmd)->prev)
			prev_r_id = get_cmd_prev((*cmd))->redirection_id;
		if ((*cmd)->prev && (*cmd)->redirection_id == prev_r_id)
			close_cmd_fd((*cmd)->prev);
		*success = redirect_fd(cmd);
		if (*success != 1)
			return (!!free_null_cmd(*configured));
		if (is_redirection_heredoc((*cmd)->redirection_id))
			(*configured)->heredoc_file = string_dup((*cmd)->heredoc_file);
		if ((*cmd)->prev && prev_r_id != REDIRECTION_PIPE && (*cmd)->args)
			append_more_args(&(*configured)->args, get_cmd_args((*cmd))->next);
		if ((*cmd)->next)
			*cmd = (*cmd)->next;
		else
			break ;
	}
	return (1);
}
