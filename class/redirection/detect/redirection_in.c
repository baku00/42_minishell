/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:13:49 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/28 02:14:55 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../redirection.h"

int	is_redirection_input(int r_id)
{
	return (r_id == REDIRECTION_INPUT);
}

int	is_redirection_heredoc(int r_id)
{
	return (r_id == REDIRECTION_HEREDOC);
}

int	is_redirection_in(int r_id)
{
	return (is_redirection_input(r_id) || is_redirection_heredoc(r_id));
}
