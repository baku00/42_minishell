/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 18:27:02 by my_name_          #+#    #+#             */
/*   Updated: 2023/03/05 23:05:11 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary.h"

static void	not_found(t_cmd *cmd)
{
	print_binary_not_found(cmd->bin);
}

void	exec_binary(char *path, t_cmd *cmd, t_env *env)
{
	char	**args;
	char	**env_vars;

	args = list_to_array(cmd->args);
	env_vars = env_to_array(env);
	close_all_fd(cmd);
	execve(path, args, env_vars);
	binary_error(path, cmd, args, env_vars);
}

void	exec_bin(t_cmd *cmd, t_env **env)
{
	char	*path;

	if (!cmd)
		exit(127);
	execute_fd(cmd);
	if (cmd->bin)
	{
		path = get_bin_path(get_string(cmd->bin), *env);
		if (!path)
			not_found(cmd);
		else if (check_access(path) != IS_FILE)
			print_binary_type_error(cmd->bin, check_access(path));
		else if (access(path, X_OK))
			print_binary_not_permission(cmd->bin);
		else
			exec_binary(path, cmd, *env);
	}
	exit(127);
}

// void	exec_bin(t_cmd *cmd, t_env **env)
// {
// 	char	*path;
// 	char	**args;
// 	char	**env_vars;

// 	if (!cmd)
// 		exit(127);
// 	execute_fd(cmd);
// 	if (cmd->bin)
// 	{
// 		path = get_bin_path(get_string(cmd->bin), *env);
// 		if (!path)
// 			not_found(cmd);
// 		else
// 		{
// 			if (access(path, X_OK))
// 				(print_binary_not_permission(cmd->bin), exit(127));
// 			close_all_fd(cmd);
// 			args = list_to_array(cmd->args);
// 			env_vars = env_to_array(*env);
// 			execve(path, args, env_vars);
// 			binary_error(path, cmd, args, env_vars);
// 		}
// 	}
// 	exit(127);
// }
