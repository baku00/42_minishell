/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:57:04 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/13 02:00:14 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

t_cmd	*get_cmd_prev(t_cmd *cmd)
{
	return (cmd->prev);
}

t_cmd	*get_cmd_next(t_cmd *cmd)
{
	return (cmd->next);
}

t_args	*get_cmd_args(t_cmd *cmd)
{
	return (cmd->args);
}

int	get_cmd_redirection_id(t_cmd *cmd)
{
	return (cmd->redirection_id);
}
