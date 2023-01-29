/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:18:37 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/28 01:53:57 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg.h"

int	append_args(t_args **args, t_string *new_arg)
{
	int	success;

	if (!(*args))
	{
		(*args) = create_args((*args), new_arg);
		return (!!(*args));
	}
	while ((*args)->next)
		(*args) = (*args)->next;
	(*args)->next = create_args((*args), new_arg);
	success = !!((*args)->next);
	while ((*args) && (*args)->prev)
		(*args) = (*args)->prev;
	return (success);
}

t_args	*create_args(t_args *prev, t_string *string)
{
	t_args	*arg;

	arg = ft_calloc(sizeof(t_args), 1);
	if (!arg)
		return (NULL);
	arg->string = string_dup(string);
	arg->type = TYPE_ARG;
	arg->info = NULL;
	arg->next = NULL;
	arg->prev = prev;
	return (arg);
}
