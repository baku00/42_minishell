/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 20:53:16 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/10 02:49:52 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	**env_to_array(t_env *env)
{
	char		**array;
	int			i;
	t_string	*entry;

	env = get_info_first(env);
	array = ft_calloc(sizeof(char *), get_info_length(env) + 1);
	if (!array)
		return (NULL);
	i = 0;
	while (env)
	{
		entry = get_entry(env);
		array[i] = ft_strdup(get_string(entry));
		free_string(entry);
		i++;
		if (env->next)
			env = env->next;
		else
			break ;
	}
	return (array);
}
