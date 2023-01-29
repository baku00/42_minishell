/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:19:11 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/28 22:49:17 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_string	*get_env_value(t_env *env)
{
	return (env->value);
}

t_string	*get_value_env_from_key(t_env *env, t_string *key)
{
	t_env	*result;

	result = get_env_from_key(env, key, 0);
	if (!result)
		return (create_string(""));
	return (string_dup(result->value));
}
