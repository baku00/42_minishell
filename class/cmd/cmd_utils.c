/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 23:25:32 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/16 23:25:40 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int	redirection(t_cmd **cmd, t_string *line, int i)
{
	if (is_redirection(line->value[i], line->value[i + 1]))
	{
		(*cmd)->redirection_id = redirection_id(line->value[i], \
		line->value[i + 1]);
		return (1);
	}
	return (0);
}
