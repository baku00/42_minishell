/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 18:36:35 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/02 19:42:43 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

int	get_string_length(t_string *str)
{
	if (!str)
		return (0);
	return (str->length);
}

char	*get_string(t_string *str)
{
	if (!str)
		return (NULL);
	return (str->value);
}
