/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 01:30:26 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/27 02:15:56 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	append_env_first(t_env **env, t_env *new)
{
	while ((*env)->prev)
		*env = (*env)->prev;
	(*env)->prev = new;
	new->next = *env;
	while ((*env)->prev)
		*env = (*env)->prev;
	get_info(*env)->first = new;
	get_info(*env)->length += 1;
}

void	append_env_last(t_env **env, t_env *new)
{
	while ((*env)->next)
		*env = (*env)->next;
	(*env)->next = new;
	new->prev = *env;
	while ((*env)->prev)
		*env = (*env)->prev;
	get_info(*env)->last = new;
	get_info(*env)->length += 1;
}
