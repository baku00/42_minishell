/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 21:41:21 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/29 00:53:39 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pwd.h"

/**
 * @param paths	path_string
 * @param charp	char_path
 * @param pwd_type	OLDPWD || PWD
 */
void	change_pwd(t_env **env, t_string *paths, char *charp, char *pwd_type)
{
	t_string	*front;

	front = create_string(pwd_type);
	paths = create_string(charp);
	append_front_string(&paths, front);
	append_var(env, paths);
	free_string(paths);
	free(charp);
	free_string(front);
}

void	exec_pwd(int display, char **path, int fd)
{
	char	buffer[1024];
	char	*cwd;

	(void) path;
	cwd = getcwd(buffer, 1024);
	if (display)
		ft_putendl_fd(cwd, fd);
	else
		*path = ft_strdup(cwd);
}
