/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_special_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 00:24:38 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/16 23:08:11 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_string	*get_home(t_env *env)
{
	t_string	*home;
	t_string	*path;

	home = create_string("HOME");
	if (!home)
		return (NULL);
	path = get_value_env_from_key(env, home);
	free_string(home);
	return (path);
}
