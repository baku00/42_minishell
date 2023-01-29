/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:07:55 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/28 16:09:53 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg.h"

t_args	*arg_dup(t_args *arg)
{
	t_args	*duplicate;

	if (!arg)
		return (NULL);
	duplicate = ft_calloc(sizeof(t_args), 1);
	if (!duplicate)
		return (NULL);
	duplicate->string = string_dup(arg->string);
	duplicate->type = arg->type;
	duplicate->prev = NULL;
	duplicate->next = NULL;
	return (duplicate);
}

t_args	*args_dup(t_args *prev, t_args *args)
{
	t_args	*duplicate;

	if (!args)
		return (NULL);
	duplicate = arg_dup(args);
	duplicate->prev = prev;
	if (args->next)
		duplicate->next = args_dup(duplicate, args->next);
	return (duplicate);
}
