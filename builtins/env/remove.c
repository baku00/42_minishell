/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:45:33 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/23 16:39:41 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	remove_env(t_env **env)
{
	t_env	*next;
	t_env	*prev;

	next = (*env)->next;
	prev = (*env)->prev;
	if (next)
		next->prev = prev;
	if (prev)
		prev->next = next;
	free_env(*env);
	if (next)
		*env = next;
	else
		*env = prev;
}
