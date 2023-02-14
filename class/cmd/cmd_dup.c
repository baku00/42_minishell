/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:40:01 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/13 01:40:06 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

t_cmd	*cmd_dup(t_cmd *prev, t_cmd *cmd)
{
	t_cmd	*dup;

	dup = init_cmd(prev);
	if (!dup)
		return (free_null_cmd(dup));
	if (prev)
		dup->fd_in = cmd->fd_in;
	dup->bin = string_dup(cmd->bin);
	dup->args = args_dup(NULL, cmd->args);
	return (dup);
}
