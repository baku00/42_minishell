/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 21:33:38 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/16 23:08:18 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	replace_env_value(t_env **env, t_string *value)
{
	free_string((*env)->value);
	if (value)
	{
		(*env)->value = string_dup(value);
		(*env)->has_value = 1;
	}
	else if ((*env)->has_value)
		(*env)->value = create_string("");
}
