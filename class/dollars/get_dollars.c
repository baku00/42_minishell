/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dollars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 01:58:19 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/29 00:27:49 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dollars.h"

int get_dollar(t_string *line, int i, t_string **current_arg, t_env *env)
{
	t_string *extracted;
	t_string *str_itoa;
	t_string *tmp;
	char *itoa;
	int result;

	extracted = get_variable_name(line, i + 1);
	if (!extracted->length)
	{
		append_char(current_arg, line->value[i]);
		free_string(extracted);
		return (0);
	}
	tmp = get_value_env_from_key(env, extracted);
	if (equals_string_to_char(extracted, "?"))
	{
		itoa = ft_itoa(g_status);
		str_itoa = create_string(itoa);
		result = ft_strlen(itoa);
		free(itoa);
		append_string(current_arg, str_itoa);
		free_string(str_itoa);
		free_string(extracted);
		free_string(tmp);
		return (result);
	}
	else if (tmp)
		append_string(current_arg, tmp);
	result = get_string_length(extracted);
	free_string(extracted);
	free_string(tmp);
	return (result);
}
