/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:49:59 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/17 01:00:18 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dollars.h"

int	is_dollars(char c)
{
	return (c == '$');
}

t_string	*get_variable_name(t_string *string, int i)
{
	char		*str;
	int			length;
	t_string	*variable;

	str = string->value;
	length = string->length;
	variable = create_string("");
	if (!variable)
		return (NULL);
	if (str[i] == '?')
	{
		append_char(&variable, str[i]);
	}
	else
	{
		while (i < length && (ft_isalpha(str[i]) || str[i] == '_'))
		{
			append_char(&variable, str[i]);
			i++;
		}
	}
	return (variable);
}

t_string	*check_for_variable(t_string *string)
{
	int			i;
	int			length;

	length = string->length;
	i = 0;
	while (i < length && !is_dollars(string->value[i]))
		i++;
	return (get_variable_name(string, i));
}

void	replace_all_variables(t_env *env, t_string **string)
{
	int			i;
	t_string	*var_name;
	t_string	*tmp;

	i = 0;
	while (i < (*string)->length)
	{
		while (i < (*string)->length && !is_dollars((*string)->value[i]))
			i++;
		if (i == (*string)->length)
			return ;
		var_name = get_variable_name(*string, i + 1);
		if (equals_string_to_char(var_name, "?"))
		{
			tmp = create_string(ft_itoa(g_status));
			replace_variable_name(string, var_name, tmp);
		}
		else
		{
			tmp = get_value_env_from_key(env, var_name);
			replace_variable_name(string, var_name, tmp);
		}
		free_string(tmp);
	}
}

/**
 * @param	s	string
 * @param	v	var_name
 * @param	r	replace
 */
void	replace_variable_name(t_string **s, t_string *v, t_string *r)
{
	append_front_char(&v, '$');
	str_replace(&(*s)->value, v->value, r->value);
	(*s)->length = ft_strlen((*s)->value);
	free_string(v);
}
