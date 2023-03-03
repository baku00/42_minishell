/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:50:24 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/02 19:50:33 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "info.h"

void	free_info(t_info *info)
{
	if (!info)
		return ;
	free(info);
}

void	reset_info(t_info *info)
{
	if (!info)
		return ;
	info->first = NULL;
	info->last = NULL;
	info->length = 0;
}
