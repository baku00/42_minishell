/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 18:27:02 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/03 00:55:21 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary.h"

static void	not_found(t_cmd *cmd)
{
	print_binary_not_found(cmd->bin);
	while (cmd->prev)
	{
		while (((t_args *)cmd->args)->prev)
			cmd->args = ((t_args *)cmd->args)->prev;
		cmd = cmd->prev;
	}
	free_all_cmd(cmd);
}

void	exec_bin(t_cmd *cmd, t_env **env)
{
	char	*path;

	if (cmd)
	{
		execute_fd(cmd);
		path = get_bin_path(get_string(cmd->bin), *env);
		if (!path)
			not_found(cmd);
		else
		{
			if (access(path, X_OK))
				return (print_binary_not_permission(cmd->bin));
			close_all_fd(cmd);
			execve(path, list_to_array(cmd->args), env_to_array(*env));
			print_binary_execution_error(cmd->bin);
		}
	}
	exit(127);
}
