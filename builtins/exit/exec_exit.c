/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 03:14:22 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/07 15:22:37 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

void	exec_exit(t_minishell *minishell, t_args *status_string, int fd)
{
	int		status;

	if (status_string)
		status = ft_atoi(get_string(status_string->string));
	else
		status = 0;
	ft_putendl_fd("exit", fd);
	free_minishell(minishell);
	exit(status);
}
