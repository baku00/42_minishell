/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 01:52:46 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/28 01:53:14 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src.h"

int	is_space(t_cmd **cmd, t_string **current_arg, t_string *line, int i)
{
	if (!(*cmd)->bin)
		(*cmd)->bin = string_dup(*current_arg);
	if (!append_full_args(&(*cmd)->args, current_arg))
		return (-1);
	return (skip_space(line, i));
}

int	skip_space(t_string *line, int i)
{
	while (line->value[i] == ' ')
		i++;
	return (i);
}
