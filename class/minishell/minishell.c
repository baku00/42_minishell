/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:23:35 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/23 22:32:04 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_tmp_dir(void)
{
	DIR				*dir;
	struct dirent	*directory;
	t_string		*tmp_dir;
	t_string		*file;

	tmp_dir = create_string("/home/user/minishell/tmp/");
	dir = opendir(tmp_dir->value);
	if (!dir)
		return ;
	directory = readdir(dir);
	file = create_string(directory->d_name);
	append_front_string(&file, tmp_dir);
	while (ft_strncmp(directory->d_name, "..", ft_strlen(directory->d_name)))
	{
		unlink(file->value);
		directory = readdir(dir);
		free_string(file);
		file = create_string(directory->d_name);
		append_front_string(&file, tmp_dir);
	}
	free_string(file);
	free_string(tmp_dir);
	closedir(dir);
}

void	*reset_minishell(t_minishell *minishell)
{
	t_info	*cmd;
	t_info	*cmd_args;
	t_info	*configured;
	t_info	*configured_args;

	cmd = get_minf_cmd(minishell);
	cmd_args = get_minishell_info_cmd_args(minishell);
	configured = get_minishell_info_configured(minishell);
	configured_args = get_minishell_info_configured_args(minishell);
	free_all_cmd(get_info_first(minishell->cmd));
	minishell->cmd = NULL;
	free_all_cmd(get_info_first(minishell->configured));
	minishell->configured = NULL;
	minishell->i = 0;
	reset_info(cmd);
	reset_info(cmd_args);
	reset_info(configured);
	reset_info(configured_args);
	minishell->fd[0] = STDIN_FILENO;
	minishell->fd[1] = STDOUT_FILENO;
	clear_tmp_dir();
	return (NULL);
}

void	*free_minishell(t_minishell *minishell)
{
	if (!minishell)
		return (NULL);
	if (minishell->env)
		free_all_env(minishell->env);
	if (minishell->cmd)
		free_all_cmd(minishell->cmd);
	if (minishell->configured)
		free_all_cmd(minishell->configured);
	if (minishell->infos)
		free_infos(minishell->infos);
	if (minishell->line != NULL)
		free_string(minishell->line);
	free(minishell->fd);
	free(minishell);
	return (NULL);
}

int	*create_fd(void)
{
	int	*fd;

	fd = ft_calloc(sizeof(int), 2);
	if (!fd)
		return (NULL);
	fd[0] = STDIN_FILENO;
	fd[1] = STDOUT_FILENO;
	return (fd);
}

t_minishell	*create_minishell(void)
{
	t_minishell	*minishell;

	minishell = ft_calloc(sizeof(t_minishell), 1);
	if (!minishell)
		return (NULL);
	minishell->env = NULL;
	minishell->cmd = NULL;
	minishell->configured = NULL;
	minishell->config = NULL;
	minishell->i = 0;
	minishell->fd = create_fd();
	minishell->infos = create_minishell_infos();
	if (!minishell->infos || !minishell->fd)
		return (free_minishell(minishell));
	return (minishell);
}
