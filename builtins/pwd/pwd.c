/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 21:41:21 by my_name_          #+#    #+#             */
/*   Updated: 2023/03/05 02:37:11 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pwd.h"

void	change_pwd(t_env **env, char *path)
{
	exec_change_pwd(env, path, PWD_TYPE);
}

void	change_old_pwd(t_env **env, char *old_path)
{
	exec_change_pwd(env, old_path, OLDPWD_TYPE);
}

void	exec_change_pwd(t_env **env, char *path, int type)
{
	t_string	*string_path;
	t_string	*string_path_value;

	if (type == PWD_TYPE)
		string_path = create_string("PWD=");
	else
		string_path = create_string("OLDPWD=");
	string_path_value = create_string(path);
	append_string(&string_path, string_path_value);
	append_var(env, string_path);
	free_string(string_path);
	free_string(string_path_value);
}

void	exec_pwd(int display, char **path, int fd)
{
	char	buffer[1024];
	char	*cwd;

	(void) path;
	cwd = getcwd(buffer, 1024);
	if (display)
	{
		ft_putendl_fd(cwd, fd);
		g_status = 0;
	}
	else
	{
		if (cwd)
			*path = ft_strdup(cwd);
		else
			*path = NULL;
	}
}
