/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 23:03:10 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/16 22:56:58 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

int	is_redirection(char c, char c2)
{
	return (
		is_pipe(c) || \
		is_input(c) || \
		is_output(c) || \
		is_heredoc(c, c2) || \
		is_append(c, c2)
	);
}

int	redirection_id(char c, char c2)
{
	if (is_pipe(c))
		return (REDIRECTION_PIPE);
	else if (is_heredoc(c, c2))
		return (REDIRECTION_HEREDOC);
	else if (is_append(c, c2))
		return (REDIRECTION_APPEND);
	else if (is_input(c))
		return (REDIRECTION_INPUT);
	else if (is_output(c))
		return (REDIRECTION_OUTPUT);
	return (0);
}
