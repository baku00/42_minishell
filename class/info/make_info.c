/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:49:58 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/07 00:06:18 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "info.h"

void	make_info_args(t_args *arg, t_info *info_arg)
{
	if (!arg)
		return ;
	arg->info = info_arg;
	if (!arg->prev)
		info_arg->first = arg;
	if (!arg->next)
		info_arg->last = arg;
	info_arg->length += 1;
	if (arg->next)
		make_info_args(arg->next, info_arg);
}

void	make_info(t_cmd *cmd, t_info *info_cmd, t_info *info_args)
{
	cmd->info = info_cmd;
	if (!cmd->prev)
		info_cmd->first = cmd;
	if (!cmd->next)
		info_cmd->last = cmd;
	info_cmd->length += 1;
	make_info_args(cmd->args, info_args);
	if (cmd->next)
		make_info(cmd->next, info_cmd, info_args);
}
