/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 18:35:54 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/16 22:52:43 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

int	equals_string(t_string *str1, t_string *str2)
{
	if (!str1 || !str2)
		return (!str1 && !str2);
	if (str1->length != str2->length)
		return (0);
	return (!compare_string(str1, str2));
}

int	equals_string_to_char(t_string *str, char *c)
{
	t_string	*compare;
	int			equals;

	if (!str || !c)
		return (!str && !c);
	compare = create_string(c);
	if (!compare)
		return (0);
	equals = equals_string(str, compare);
	free_string(compare);
	return (equals);
}

int	compare_string(t_string *str1, t_string *str2)
{
	return (ft_strncmp(str1->value, str2->value, str1->length));
}
