/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:15:48 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/16 23:21:35 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

void	execute_fd(int fd, int std)
{
	if (fd != std)
	{
		dup2(fd, std);
		close(fd);
	}
}

void	close_fd(int fd, int std)
{
	if (fd != std)
		close(fd);
}
