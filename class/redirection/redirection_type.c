/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 22:56:51 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/16 22:56:29 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

int	is_pipe(char c)
{
	return (c == '|');
}

int	is_input(char c)
{
	return (c == '<');
}

int	is_output(char c)
{
	return (c == '>');
}

int	is_heredoc(char c, char c2)
{
	return (is_input(c) && is_input(c2));
}

int	is_append(char c, char c2)
{
	return (is_output(c) && is_output(c2));
}
