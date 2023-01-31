/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 04:42:51 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/30 15:50:40 by my_name_         ###   ########.fr       */
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

void	append_or_replace(t_env *var, t_env **e, t_string *k, t_string *v)
{
	if (!var)
		append_env_last(e, init_env(k, v));
	else
	{
		while (var != *e && (*e)->next)
			*e = (*e)->next;
		if (var == *e)
			replace_env_value(e, v);
	}
	free_string(k);
	free_string(v);
}

int	append_var(t_env **env, t_string *args)
{
	t_string	*key;
	t_string	*var_name;
	t_string	*value;
	t_env		*env_var;
	int			i;

	i = 0;
	*env = get_info_first(*env);
	var_name = get_variable_name(args, i);
	key = extract_string_into(get_string(args), '=', &i);
	if (!key->length)
	{
		free_string(var_name);
		free_string(key);
		return (KEY_EMPTY);
	}
	else if (!equals_string(key, var_name))
	{
		free_string(var_name);
		free_string(key);
		return (KEY_INVALID);
	}
	if (key->length != get_string_length(args))
	{
		value = extract_value(args, key);
		if (!value)
			return (0);
	}
	else
		value = NULL;
	env_var = get_env_from_key(*env, key, 0);
	free_string(var_name);
	append_or_replace(env_var, env, key, value);
	return (1);
}
