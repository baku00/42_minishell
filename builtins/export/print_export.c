/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 22:19:32 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/16 23:05:50 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

void	print_export(t_env *env, int fd)
{
	ft_putstr_fd(get_string(env->key), fd);
	if (env->has_value)
	{
		ft_putchar_fd('=', fd);
		ft_putstr_fd(get_string(env->value), fd);
	}
	ft_putstr_fd("\n", fd);
	if (env->next)
		print_export(env->next, fd);
}
