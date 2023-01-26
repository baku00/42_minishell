/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 03:55:44 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/24 16:44:32 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

int is_redirection_output(int r_id)
{
	return (r_id == REDIRECTION_OUTPUT);
}

int is_redirection_append(int r_id)
{
	return (r_id == REDIRECTION_APPEND);
}

int is_redirection_out(int r_id)
{
	return (is_redirection_output(r_id) || is_redirection_append(r_id));
}

int is_redirection_input(int r_id)
{
	return (r_id == REDIRECTION_INPUT);
}

int is_redirection_heredoc(int r_id)
{
	return (r_id == REDIRECTION_HEREDOC);
}

int is_redirection_in(int r_id)
{
	return (is_redirection_input(r_id) || is_redirection_heredoc(r_id));
}

int is_redirection_in_or_out(int r_id)
{
	return (is_redirection_in(r_id) || is_redirection_out(r_id));
}

int	is_redirection_pipe(int r_id)
{
	return (r_id == REDIRECTION_PIPE);
}