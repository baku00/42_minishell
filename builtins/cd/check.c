/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:02:35 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/11 16:02:51 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

int	check_path(t_args **path, t_env **env)
{
	t_env	*home;

	home = get_env_from_char_key(*env, "HOME", 0);
	if (!(*path))
	{
		*path = create_args(NULL, home->value);
		return (1);
	}
	else if (!(*path)->string)
	{
		(*path)->string = home->value;
		return (1);
	}
	else if (!get_string_length((*path)->string))
	{
		(*path)->string = home->value;
		return (1);
	}
	return (0);
}
