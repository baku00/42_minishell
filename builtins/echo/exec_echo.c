/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 01:29:46 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/03 16:53:20 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"

static void	show_empty_args(int fd)
{
	ft_putchar_fd('\n', fd);
}

static void	echo_print_args(t_args *args, int fd)
{
	while (args)
	{
		ft_putstr_fd(get_string(args->string), fd);
		if (args->next)
		{
			args = args->next;
			ft_putchar_fd(' ', fd);
		}
		else
			break ;
	}
}

void	exec_echo(t_args *args, int fd)
{
	int	n;
	int	length;

	if (!args)
		return (show_empty_args(fd));
	length = get_string_length(args->string);
	n = ft_strncmp(get_string(args->string), "-n", length);
	if (!n)
	{
		if (!args->next)
			return ;
		else
			args = args->next;
	}
	echo_print_args(args, fd);
	if (n)
	ft_putchar_fd('\n', fd);
}
