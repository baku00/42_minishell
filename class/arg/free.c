/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 01:48:22 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/28 01:48:28 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg.h"

void	free_args(t_args *args)
{
	if (!args)
		return ;
	if (args->string)
		free_string(args->string);
	free(args);
}

void	args_free_all(t_args *args)
{
	if (!args)
		return ;
	while (args->next)
	{
		args = args->next;
		free_args(args->prev);
	}
	if (args)
		free_args(args);
}
