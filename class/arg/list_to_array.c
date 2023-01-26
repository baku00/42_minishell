/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 18:33:17 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/16 22:49:15 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg.h"

static int	list_length(t_args *arg)
{
	int	i;

	i = 0;
	while (arg)
	{
		i++;
		if (arg->next)
			arg = arg->next;
		else
			break ;
	}
	return (i);
}

char	**list_to_array(t_args *arg)
{
	char	**args;
	int		length;
	int		i;

	length = list_length(arg);
	args = ft_calloc(sizeof(char *), length + 1);
	i = 0;
	while (arg)
	{
		free(args[i]);
		args[i] = ft_strdup(get_string(arg->string));
		i++;
		if (arg->next)
			arg = arg->next;
		else
			break ;
	}
	return (args);
}
