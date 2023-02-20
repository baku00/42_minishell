/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 22:19:08 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/19 01:58:38 by my_name_         ###   ########.fr       */
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
	g_status = 0;
	if (appended != 1)
		g_status = 127;
}

t_env	*export_dup(t_env *prev, t_env *env, t_info **info)
{
	t_env	*export;

	export = env_dup(env);
	export->info = (*info);
	export->prev = prev;
	export->next = NULL;
	(*info)->length += 1;
	if (!prev)
		(*info)->first = export;
	if (env->next)
		export->next = export_dup(export, env->next, info);
	else
		(*info)->last = export;
	return (export);
}

void	exec_export(t_cmd *cmd, t_env *env)
{
	t_env	*export;
	t_info	*info_export;

	if (cmd->args && !((t_args *) cmd->args)->next)
	{
		info_export = create_info();
		export = export_dup(NULL, get_info_first(env), &info_export);
		export = get_info_first(export);
		print_export(export, cmd->fd_out);
		free_info(info_export);
		g_status = 0;
	}
	else
		append_vars(&env, cmd->args->next);
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
