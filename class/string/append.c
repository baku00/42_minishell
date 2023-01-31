/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 23:08:58 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/30 22:54:50 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

static char	*char_to_string(char c)
{
	char	*str;

	str = ft_calloc(sizeof(char), 2);
	if (!str)
		return (NULL);
	str[0] = c;
	return (str);
}

int	append_char(t_string **string, char c)
{
	char	*char_str;

	char_str = char_to_string(c);
	if (!char_str || !(*string))
		return (0);
	(*string)->value = ft_strjoin((*string)->value, char_str);
	free(char_str);
	if (!(*string)->value)
		return (0);
	(*string)->length += 1;
	return (1);
}

int	append_front_char(t_string **string, char c)
{
	char	*char_str;
	char	*str;

	char_str = char_to_string(c);
	if (!char_str || !(*string))
		return (0);
	str = ft_strdup((*string)->value);
	free((*string)->value);
	(*string)->value = ft_strjoin(char_str, str);
	free(str);
	if (!(*string)->value)
		return (0);
	(*string)->length += 1;
	return (1);
}

int	append_string(t_string **string, t_string *append)
{
	if (!append || !(*string))
		return (0);
	(*string)->value = ft_strjoin((*string)->value, append->value);
	if (!(*string)->value)
		return (0);
	(*string)->length += append->length;
	return (1);
}

int	append_front_string(t_string **string, t_string *append)
{
	t_string	*duplicate;

	if (!append || !(*string))
		return (0);
	duplicate = string_dup(append);
	append_string(&duplicate, *string);
	if (!duplicate)
		return (0);
	free_string(*string);
	*string = string_dup(duplicate);
	free_string(duplicate);
	if (!string)
		return (0);
	return (1);
}
