/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 22:19:08 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/28 22:26:18 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

void	print_error(int appended)
{
	if (appended == KEY_EMPTY || appended == KEY_INVALID)
		ft_putendl_fd("Erreur: la clé est invalide", STDERR_FILENO);
}

void	exec_export(t_cmd *cmd, t_env *env)
{
	t_args	*next;
	int		fd;
	int		appended;

	fd = cmd->fd_out;
	if (cmd->next)
		fd = STDIN_FILENO;
	next = ((t_args *)cmd->args)->next;
	if (!next)
		print_export(env, fd);
	else
	{
		appended = \
		append_var(&env, ((t_args *)((t_args *)cmd->args)->next)->string);
		print_error(appended);
	}
}
