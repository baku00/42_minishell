/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 21:00:20 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/27 01:49:33 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_builtin(t_string *cmd, char *builtin, int id)
{
	t_string	*string;

	string = create_string(builtin);
	if (!string)
		return (-1);
	if (equals_string(cmd, string))
		return (id);
	free_string(string);
	return (0);
}

int	is_builtins(t_string *cmd)
{
	int	builtin;

	builtin = is_builtin(cmd, "echo", ECHO_CMD);
	if (builtin)
		return (builtin);
	builtin = is_builtin(cmd, "cd", CD);
	if (builtin)
		return (builtin);
	builtin = is_builtin(cmd, "pwd", PWD);
	if (builtin)
		return (builtin);
	builtin = is_builtin(cmd, "export", EXPORT);
	if (builtin)
		return (builtin);
	builtin = is_builtin(cmd, "unset", UNSET);
	if (builtin)
		return (builtin);
	builtin = is_builtin(cmd, "env", ENV);
	if (builtin)
		return (builtin);
	builtin = is_builtin(cmd, "exit", EXIT);
	if (builtin)
		return (builtin);
	return (0);
}

void	exec_builtins(t_cmd *cmd, t_env *env)
{
	int	builtin;
	int	fd;

	fd = cmd->fd_out;
	if (cmd->next)
		fd = STDIN_FILENO;
	env = get_info_first(env);
	builtin = is_builtins(cmd->bin);
	if (builtin == ENV)
		exec_env(cmd, env);
	else if (builtin == PWD)
		exec_pwd(1, NULL, fd);
	else if (builtin == EXPORT)
		exec_export(cmd, env);
	else if (builtin == UNSET)
		exec_unset(env, ((t_args *)cmd->args)->next);
	else if (builtin == CD)
		exec_cd(((t_args *)cmd->args)->next, &env);
	else if (builtin == ECHO_CMD)
		exec_echo(((t_args *)cmd->args)->next, fd);
}
