/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 23:44:26 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/16 22:51:14 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

int	remove_char(t_string **string, int i)
{
	t_string	*before;
	t_string	*after;

	if (i >= 1)
		before = create_string(ft_substr((*string)->value, 0, i));
	after = create_string(
			ft_substr((*string)->value, i + 1, (*string)->length - i)
			);
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
