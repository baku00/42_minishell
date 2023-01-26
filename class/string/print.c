/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 23:23:44 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/16 22:52:58 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

void	print_string(t_string *str)
{
	if (!str)
		return ;
	printf("Value: (%s)\n", str->value);
	printf("Length: (%d)\n", str->length);
}
