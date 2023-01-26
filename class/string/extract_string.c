/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 01:06:13 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/16 22:50:32 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

t_string	*extract_string_into(char *str, char c, int *i)
{
	t_string	*extracted;

	extracted = create_string("");
	if (!extracted)
		return (NULL);
	if (str[*i] == c)
		(*i) += 1;
	while (str[*i] && str[*i] != c)
	{
		if (!append_char(&extracted, str[*i]))
			return (free_string(extracted));
		(*i) += 1;
	}
	return (extracted);
}
