/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 03:55:44 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/28 02:14:23 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

int	is_redirection_in_or_out(int r_id)
{
	return (is_redirection_in(r_id) || is_redirection_out(r_id));
}

int	is_redirection_pipe(int r_id)
{
	return (r_id == REDIRECTION_PIPE);
}
