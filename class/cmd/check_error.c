/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:04:10 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/30 21:56:05 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

t_cmd	*check_error(t_cmd *cmd)
{
	int	is_in_or_out;
	int	is_out;
	int	is_pipe;

	while (cmd)
	{
		is_in_or_out = is_redirection_in_or_out(cmd->redirection_id);
		is_out = is_redirection_out(cmd->redirection_id);
		is_pipe = is_redirection_pipe(cmd->redirection_id);
		if (is_in_or_out || is_out || is_pipe)
		{
			if (!cmd->next)
				return (cmd);
			else if (cmd->next && !((t_cmd *)cmd->next)->bin)
				return (cmd);
		}
		if (cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
	return (NULL);
}
