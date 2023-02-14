/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 21:00:20 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/11 16:09:07 by my_name_         ###   ########.fr       */
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
	{
		free_string(string);
		return (id);
	}
	free_string(string);
	return (0);
}

int	is_builtins(t_string *cmd)
{
	int	builtin;

	if (!cmd)
		return (0);
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
	return (is_builtin(cmd, "exit", EXIT));
}

void	exec_builtins(t_minishell *minishell, t_cmd *cmd, t_env **env)
{
	int	builtin;
	int	fd;

	fd = cmd->fd_out;
	*env = get_info_first(*env);
	builtin = is_builtins(cmd->bin);
	(void) minishell;
	if (builtin == ENV)
		exec_env(cmd, *env);
	else if (builtin == PWD)
		exec_pwd(1, NULL, fd);
	else if (builtin == EXPORT)
		exec_export(cmd, *env);
	else if (builtin == UNSET)
		exec_unset(env, ((t_args *)cmd->args)->next);
	else if (builtin == CD)
		exec_cd(((t_args *)cmd->args)->next, env);
	else if (builtin == ECHO_CMD)
		exec_echo(((t_args *)cmd->args)->next, fd);
	else if (builtin == EXIT)
		exec_exit(minishell, ((t_args *)cmd->args)->next, fd);
	close_fd(cmd->fd_in, STDIN_FILENO);
	close_fd(cmd->fd_out, STDOUT_FILENO);
}
