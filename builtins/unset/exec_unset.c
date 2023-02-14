/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 22:31:53 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/12 01:27:55 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

void	unset(t_env **env, t_string *var_name)
{
	while ((*env)->next && !equals_string((*env)->key, var_name))
		(*env) = (*env)->next;
	if (equals_string((*env)->key, var_name))
	{
		remove_env(env);
		*env = get_info_first(*env);
	}
}

void	exec_unset(t_env **env, t_args *args)
{
	t_string	*var_name;

	var_name = NULL;
	while (args)
	{
		var_name = get_variable_name(args->string, 0);
		if (!equals_string(var_name, args->string))
		{
			print_invalid_params(args->string);
			if (!args->next)
				break ;
			args = args->next;
			continue ;
		}
		unset(env, var_name);
		*env = get_info_first(*env);
		if (!args->next)
			break ;
		args = args->next;
		free_string(var_name);
		var_name = NULL;
	}
	if (var_name)
		free_string(var_name);
}
