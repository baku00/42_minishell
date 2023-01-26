/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 21:43:47 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/02 20:49:17 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	*free_env(t_env *env)
{
	if (env->key)
		free_string(env->key);
	if (env->value)
		free_string(env->value);
	free(env);
	return (NULL);
}
