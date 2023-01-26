/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 21:41:21 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/22 22:16:40 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pwd.h"

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
