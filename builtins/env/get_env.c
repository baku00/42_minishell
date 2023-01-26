/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 20:49:29 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/26 17:24:16 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_string	*get(char *envp, int i, int length)
{
	char		*substr;
	t_string	*string;

	substr = ft_substr(envp, i, length);
	if (!substr)
		return (NULL);
	string = create_string(substr);
	free(substr);
	return (string);
}

t_string	*get_env_value(t_env *env)
{
	return (env->value);
}

t_string	*get_env_key(t_env *env)
{
	return (env->key);
}

t_env	*get_env_from_key(t_env *env, t_string *key)
{
	if (!env || !key)
		return (NULL);
	env = get_info_first(env);
	while (env)
	{
		if (!equals_string(env->key, key))
			env = env->next;
		else
			return (env);
	}
	return (NULL);
}

t_env	*get_env_from_char_key(t_env *env, char *key_char, int have_to_free)
{
	t_string	*key;

	if (!env || !key_char)
		return (NULL);
	key = create_string(key_char);
	if (have_to_free)
		free(key_char);
	if (!key)
		return (NULL);
	return (get_env_from_key(env, key));
}

t_string	*get_value_env_from_key(t_env *env, t_string *key)
{
	t_env	*result;

	result = get_env_from_key(env, key);
	if (!result)
		return (create_string(""));
	return (result->value);
}

t_string	*get_entry(t_env *env)
{
	t_string	*key_value;

	key_value = string_dup(env->key);
	append_char(&key_value, '=');
	append_string(&key_value, env->value);
	return (key_value);
}
