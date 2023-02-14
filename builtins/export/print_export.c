/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 22:19:32 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/12 00:19:53 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

void	print_current(t_env *current, int fd)
{
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(get_string(current->key), fd);
	if (current->has_value)
	{
		ft_putstr_fd("=\"", fd);
		ft_putstr_fd(get_string(current->value), fd);
	}
	ft_putendl_fd("\"", fd);
}

t_env	*find_first(t_env *env)
{
	t_env	*first;

	env = get_info_first(env);
	first = env;
	while (env->next)
	{
		env = env->next;
		if (compare_string(first->key, env->key) > 0)
			first = env;
	}
	return (first);
}

void	print_export(t_env *env, int fd)
{
	t_env	*first;
	t_args	*key;

	first = find_first(env);
	env = get_info_first(env);
	print_current(first, fd);
	key = create_args(NULL, first->key);
	exec_unset(&env, key);
	free_args(key);
	if (env && env->next)
		print_export(env->next, fd);
	else if (env)
	{
		print_current(env, fd);
		free_all_env(env);
	}
}
