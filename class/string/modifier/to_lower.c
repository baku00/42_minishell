/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_lower.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 04:22:19 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/29 04:27:32 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../string.h"

t_string	*string_to_lower(t_string *string)
{
	t_string	*lower;

	if (!string)
		return (NULL);
	lower = string_dup(string);
	string_go_to_lower(&lower);
	return (lower);
}

void	string_go_to_lower(t_string **string)
{
	int	i;

	if (!*string)
		return ;
	i = 0;
	while (i < (*string)->length)
	{
		(*string)->value[i] = ft_tolower((*string)->value[i]);
		i++;
	}
}