/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:31:53 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/29 05:03:30 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

void	unset(t_env *env, t_string *var_name)
{
	while (env->next && !equals_string(env->key, var_name))
		env = env->next;
	if (equals_string(env->key, var_name))
		remove_env(&env);
}

void	exec_unset(t_env *env, t_args *args)
{
	t_string	*var_name;

	var_name = NULL;
	while (args)
	{
		var_name = get_variable_name(args->string, 0);
		if (!equals_string(var_name, args->string))
		{
			ft_putstr_fd("Nom invalide: ", STDERR_FILENO);
			ft_putendl_fd(get_string(args->string), STDERR_FILENO);
			if (!args->next)
				break ;
			args = args->next;
			continue ;
		}
		unset(env, var_name);
		env = get_info_first(env);
		if (!args->next)
			break ;
		args = args->next;
	}
	if (var_name)
		free_string(var_name);
}
