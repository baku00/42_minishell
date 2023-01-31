/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 22:19:08 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/30 17:15:55 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

void	print_error(int appended, t_string *key)
{
	if (appended == KEY_EMPTY || appended == KEY_INVALID)
	{
		ft_putstr_fd("Erreur: la clé '", STDERR_FILENO);
		ft_putstr_fd(key->value, STDERR_FILENO);
		ft_putendl_fd("' est invalide", STDERR_FILENO);
	}
}

void	append_vars(t_env **env, t_args *args)
{
	int	appended;

	appended = 1;
	while (args->next)
	{
		*env = get_info_first(*env);
		appended = append_var(env, args->string);
		if (appended != 1)
			print_error(appended, args->string);
		args = args->next;
	}
	*env = get_info_first(*env);
	if (args)
		appended = append_var(env, args->string);
	if (appended != 1)
		print_error(appended, args->string);
}

void	exec_export(t_cmd *cmd, t_env *env)
{
	env = get_info_first(env);
	if (!((t_args *) cmd->args)->next)
		print_export(env, cmd->fd_out);
	else
		append_vars(&env, ((t_args *) get_info_first(cmd->args))->next);
	env = get_info_first(env);
}

// void	exec_export(t_cmd *cmd, t_env *env)
// {
// 	t_args	*next;
// 	int		fd;
// 	int		appended;

// 	fd = cmd->fd_out;
// 	if (cmd->next)
// 		fd = STDIN_FILENO;
// 	next = ((t_args *)cmd->args)->next;
// 	if (!next)
// 		print_export(env, fd);
// 	else
// 	{
// 		appended =
// 		append_var(&env, ((t_args *)((t_args *)cmd->args)->next)->string);
// 		print_error(appended);
// 	}
// }
