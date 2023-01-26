/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 04:42:51 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/16 23:06:31 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

t_string	*extract_value(t_string *string, t_string *key)
{
	int			start;
	char		*substr;
	t_string	*value;

	start = key->length + 1;
	substr = ft_substr(string->value, start, string->length - start);
	if (!substr)
		return (NULL);
	value = create_string(substr);
	free(substr);
	return (value);
}

int	append_var(t_env **env, t_string *args)
{
	t_string	*key;
	t_string	*var_name;
	t_string	*value;
	t_env		*env_var;
	int			i;

	i = 0;
	var_name = get_variable_name(args, i);
	key = extract_string_into(get_string(args), '=', &i);
	if (!key->length)
		return (KEY_EMPTY);
	else if (!equals_string(key, var_name))
		return (KEY_INVALID);
	if (key->length != get_string_length(args))
	{
		value = extract_value(args, key);
		if (!value)
			return (0);
	}
	else
		value = NULL;
	env_var = get_env_from_key(*env, key);
	if (!env_var)
		append_env_last(env, init_env(key, value));
	else
	{
		while (env_var != *env && (*env)->next)
			*env = (*env)->next;
		if (env_var == *env)
			replace_env_value(env, value);
	}
	return (!!get_info_last(env));
}
