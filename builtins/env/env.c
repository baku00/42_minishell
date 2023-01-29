/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 20:59:44 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/28 16:38:18 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env	*init_env(t_string *key, t_string *value)
{
	t_env	*env;

	env = ft_calloc(sizeof(t_env), 1);
	if (!env)
		return (NULL);
	env->key = string_dup(key);
	if (!env->key)
		return (free_env(env));
	env->value = string_dup(value);
	if (!env->value && value)
		return (free_env(env));
	env->type = TYPE_ENV;
	env->has_value = !!value;
	env->index = 0;
	env->sorted = NULL;
	env->info = NULL;
	env->prev = NULL;
	env->next = NULL;
	return (env);
}

void	set_env_value(t_env **env, t_string *value)
{
	(*env)->value = value;
}

static void	check_prev(t_env **prev, t_info **info, t_env **env)
{
	if (*prev)
		(*env)->index = (*prev)->index + 1;
	else
		(*env)->index = 1;
	if (!(*prev))
		update_info((*info), (*env), (*env));
	else
		update_info((*info), (*info)->first, (*env));
}

static void	free_key_value(t_string *key, t_string *value)
{
	free_string(key);
	free_string(value);
}

t_env	*generate_env(t_env *prev, t_info *info, char **envp, int i)
{
	t_env		*env;
	t_string	*key;
	t_string	*value;
	int			start_extract;

	start_extract = 0;
	key = extract_string_into(envp[i], '=', &start_extract);
	if (!key)
		return (NULL);
	value = get(envp[i], key->length + 1, ft_strlen(envp[i]) - key->length - 1);
	if (!value)
		return (free_string(key));
	env = init_env(key, value);
	free_key_value(key, value);
	env->info = info;
	env->prev = prev;
	check_prev(&prev, &info, &env);
	if (envp[i + 1])
	{
		env->next = generate_env(env, info, envp, i + 1);
		if (!env->next)
			return (free_env(env));
	}
	return (env);
}
