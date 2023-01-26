/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 18:27:02 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/16 23:21:21 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary.h"

static t_string	*get_full_path(t_string *bin, t_string *path)
{
	char		**paths;
	t_string	*current_path;
	t_string	*binary;
	int			i;

	if (get_string(bin)[0] == '/')
		return (bin);
	binary = string_dup(bin);
	paths = ft_split(get_string(path), ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		current_path = create_string(paths[i]);
		append_char(&current_path, '/');
		append_string(&current_path, binary);
		if (access(get_string(current_path), F_OK) == 0)
			return (current_path);
		free_string(current_path);
		i++;
	}
	return (NULL);
}

static void	execute_fd_binary(t_cmd *cmd)
{
	execute_fd(cmd->fd_out, STDOUT_FILENO);
	execute_fd(cmd->fd_in, STDIN_FILENO);
}

static void	finish_binary(t_cmd *cmd, int pid)
{
	close_fd(cmd->fd_in, STDIN_FILENO);
	close_fd(cmd->fd_out, STDOUT_FILENO);
	cmd->pid = pid;
}

void	exec_binary(t_cmd *cmd, t_env *env)
{
	int			pid;
	char		**args;
	t_string	*path;

	env = get_info_first(env);
	pid = fork();
	if (pid == 0)
	{
		execute_fd_binary(cmd);
		args = list_to_array(cmd->args);
		path = get_full_path(cmd->bin,
				get_value_env_from_key(env, create_string("PATH")));
		if (!path)
			printf("%s: Commande introuvable\n", get_string(cmd->bin));
		else
		{
			execve(get_string(path), args, env_to_array(env));
			perror("Erreur d'éxecution\n");
		}
		exit(127);
	}
	else
		finish_binary(cmd, pid);
}
