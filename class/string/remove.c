/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 23:44:26 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/10 03:09:08 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

int	remove_char(t_string **string, int i)
{
	t_string	*before;
	t_string	*after;
	char		*substr;

	if (i >= 1)
	{
		substr = ft_substr((*string)->value, 0, i);
		before = create_string(substr);
		free(substr);
		substr = NULL;
	}
	substr = ft_substr((*string)->value, i + 1, (*string)->length - i);
	after = create_string(substr);
	free(substr);
	substr = NULL;
	free_string(*string);
	if (i == 0)
	{
		(*string) = string_dup(after);
		return (!!(*string));
	}
	else
		(*string) = string_dup(before);
	return (append_string(string, after));
}
