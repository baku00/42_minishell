/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 18:29:45 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/16 22:51:26 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

void	*free_string(t_string *string)
{
	if (!string)
		return (NULL);
	if (string->value)
		free(string->value);
	free(string);
	return (NULL);
}

t_string	*string_dup(t_string *string)
{
	t_string	*new_string;

	if (!string)
		return (NULL);
	new_string = create_string(string->value);
	return (new_string);
}

t_string	*create_string(char *str)
{
	t_string	*string;

	if (!str)
		return (NULL);
	string = ft_calloc(sizeof(t_string), 1);
	if (!string)
		return (NULL);
	string->value = ft_strdup(str);
	string->length = 0;
	if (!string->value)
	{
		free(string);
		return (NULL);
	}
	string->length = ft_strlen(str);
	return (string);
}
