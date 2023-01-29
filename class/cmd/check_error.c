/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:04:10 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/28 02:11:27 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

t_cmd	*check_error(t_cmd *cmd)
{
	while (cmd)
	{
		if (is_redirection_in_or_out(cmd->redirection_id) || \
		is_redirection_pipe(cmd->redirection_id))
		{
			if (!cmd->next)
				return (cmd);
			else if (cmd->prev && !((t_cmd *) cmd->prev)->bin)
				return (cmd);
		}
		if (cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
	return (NULL);
}
