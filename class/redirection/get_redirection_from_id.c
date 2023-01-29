/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirection_from_id.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:31:42 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/28 02:13:05 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

char	*get_redirection_from_id(int r_id)
{
	char	*redirection;

	redirection = ft_calloc(sizeof(char), 3);
	if (!redirection)
		return (NULL);
	if (r_id == REDIRECTION_OUTPUT || r_id == REDIRECTION_APPEND)
		redirection[0] = '>';
	if (r_id == REDIRECTION_APPEND)
		redirection[1] = '>';
	if (r_id == REDIRECTION_INPUT || r_id == REDIRECTION_HEREDOC)
		redirection[0] = '<';
	if (r_id == REDIRECTION_HEREDOC)
		redirection[1] = '<';
	if (r_id == REDIRECTION_PIPE)
		redirection[0] = '|';
	return (redirection);
}
