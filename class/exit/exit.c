/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 21:16:47 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/16 23:14:07 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

void	create_exit_manager(void)
{
	g_exit_manager.string = create_string("exit");
	set_have_to_exit(!g_exit_manager.string);
}

void	set_have_to_exit(int state)
{
	g_exit_manager.have_to_exit = state;
}

int	have_to_exit(void)
{
	return (g_exit_manager.have_to_exit);
}

t_string	*get_exit_string(void)
{
	return (g_exit_manager.string);
}

void	clear_exit_manager(void)
{
	if (g_exit_manager.string)
		free_string(g_exit_manager.string);
	set_have_to_exit(0);
}
