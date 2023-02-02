/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 22:04:23 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/02 19:50:18 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "info.h"

t_info	*create_info(void)
{
	t_info	*info;

	info = ft_calloc(sizeof(t_info), 1);
	if (!info)
		return (NULL);
	info->first = NULL;
	info->last = NULL;
	info->length = 0;
	return (info);
}

void	update_info(t_info *info, void *first, void *last)
{
	info->first = first;
	info->last = last;
	info->length += 1;
}
