/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 22:20:44 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/13 01:56:54 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "info.h"

t_info	*get_info(void *list)
{
	if (!list)
		return (NULL);
	if (((t_env *) list)->type == TYPE_ENV)
		return (((t_env *) list)->info);
	else if (((t_cmd *) list)->type == TYPE_CMD)
		return (((t_cmd *) list)->info);
	else if (((t_args *)list)->type == TYPE_ARG)
		return (((t_args *)list)->info);
	return (NULL);
}

void	*get_info_first(void *list)
{
	t_info	*info;

	if (!list)
		return (NULL);
	info = get_info(list);
	if (!info)
		return (NULL);
	return (info->first);
}

void	*get_info_last(void *list)
{
	t_info	*info;

	if (!list)
		return (NULL);
	info = get_info(list);
	if (!info)
		return (NULL);
	return (info->last);
}

int	get_info_length(void *list)
{
	t_info	*info;

	if (!list)
		return (-1);
	info = get_info(list);
	if (!info)
		return (-1);
	return (info->length);
}
