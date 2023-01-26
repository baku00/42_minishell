/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:53:16 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/16 23:07:05 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	**env_to_array(t_env *env)
{
	char	**array;
	int		i;

	env = get_info_first(env);
	array = ft_calloc(sizeof(char *), get_info_length(env) + 1);
	if (!array)
		return (NULL);
	i = 0;
	while (env)
	{
		array[i] = ft_strdup(get_string(get_entry(env)));
		i++;
		if (env->next)
			env = env->next;
		else
			break ;
	}
	return (array);
}
