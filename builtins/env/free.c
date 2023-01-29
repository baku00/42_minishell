/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 21:43:47 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/28 02:18:53 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	*free_env(t_env *env)
{
	if (!env)
		return (NULL);
	if (env->key)
		free_string(env->key);
	if (env->value)
		free_string(env->value);
	free(env);
	return (NULL);
}

void	*free_all_env(t_env *env)
{
	if (!env)
		return (NULL);
	env = get_info_first(env);
	while (env->next)
	{
		env = env->next;
		free_env(env->prev);
	}
	if (env)
		free_env(env);
	return (NULL);
}
