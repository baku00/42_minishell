/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:13:49 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/28 02:15:22 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../redirection.h"

int	is_redirection_output(int r_id)
{
	return (r_id == REDIRECTION_OUTPUT);
}

int	is_redirection_append(int r_id)
{
	return (r_id == REDIRECTION_APPEND);
}

int	is_redirection_out(int r_id)
{
	return (is_redirection_output(r_id) || is_redirection_append(r_id));
}
