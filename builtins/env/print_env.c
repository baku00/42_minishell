/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 20:54:54 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/22 22:15:37 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	print_env(t_cmd *cmd, t_env *env)
{
	int	fd;

	fd = cmd->fd_out;
	ft_putstr_fd(get_string(env->key), fd);
	if (env->has_value)
	{
		ft_putchar_fd('=', fd);
		ft_putstr_fd(get_string(env->value), fd);
	}
	ft_putchar_fd('\n', fd);
	if (env->next)
		print_env(cmd, env->next);
}
