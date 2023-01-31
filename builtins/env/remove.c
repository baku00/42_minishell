/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:45:33 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/30 16:22:26 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static void	remove_first_env(t_env **env)
{
	t_env	*next;

	next = (*env)->next;
	get_info(next)->first = next;
	free_env(*env);
	*env = NULL;
	*env = next;
	(*env)->prev = NULL;
	printf("Next: %p\n", next);
}

static void	remove_last_env(t_env **env)
{
	t_env	*prev;

	prev = (*env)->prev;
	get_info(*env)->last = prev;
	free_env(*env);
	*env = NULL;
	*env = prev;
	prev->next = NULL;
}

static void	remove_into_env(t_env **env)
{
	t_env	*next;
	t_env	*prev;

	next = (*env)->next;
	prev = (*env)->prev;
	free_env(*env);
	*env = NULL;
	*env = next;
	next->prev = prev;
	prev->next = next;
}

void	remove_env(t_env **env)
{
	if (get_info_first(*env) == *env)
		remove_first_env(env);
	else if (get_info_last(*env) == *env)
		remove_last_env(env);
	else
		remove_into_env(env);
	get_info(*env)->length -= 1;
}
