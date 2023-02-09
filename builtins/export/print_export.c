/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 22:19:32 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/09 20:02:47 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

// void	print_export(t_env *env, int fd)
// {
// 	ft_putstr_fd(get_string(env->key), fd);
// 	if (env->has_value)
// 	{
// 		ft_putchar_fd('=', fd);
// 		ft_putstr_fd(get_string(env->value), fd);
// 	}
// 	ft_putstr_fd("\n", fd);
// 	if (env->next)
// 		print_export(env->next, fd);
// }

void	print_current(t_env *current, int fd)
{
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(get_string(current->key), fd);
	ft_putstr_fd("=\"", fd);
	ft_putstr_fd(get_string(current->value), fd);
	ft_putendl_fd("\"", fd);
}

void first(t_env **env)
{
	while ((*env)->prev)
		(*env) = (*env)->prev;
}

void	print_export(t_env *env, int fd)
{
	t_env	*current;
	int		compare;
	int		length;

	current = env;
	if (env->next)
	{
		env = env->next;
		compare = compare_string(current->key, env->key);
		while (compare)
		{
			if (compare > 0)
				current = env;
			if (env->next)
				env = env->next;
			else
				break ;
			compare = compare_string(current->key, env->key);
		}
	}
	print_current(current, fd);
	length = get_info_length(current);
	remove_env(&current);
	if (length >= 2)
	{
		env = get_info_first(env);
		print_export(env, fd);
	}
}
