/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 22:28:28 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/04 01:23:24 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	sort_env(t_env **env, t_env *src, int last)
{
	t_env	*tmp;

	if (!(*env))
		(*env) = env_dup(src);
	while ((*env)->prev && compare_string((*env)->key, src->key) > 0)
		(*env) = (*env)->prev;
	if (!(*env)->prev)
		(*env)->prev = env_dup(src);
	else
	{
		tmp = (*env)->prev;
		src->prev = tmp;
		(*env)->prev = src;
	}
	printf("Src\n");
	print_string(src->key);
	printf("\n");
	sort_env(env, src->next, last);
}
