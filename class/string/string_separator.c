/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_separator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 22:38:18 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/16 22:50:11 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

int	is_guillemet(char c)
{
	return (c == '"');
}

int	is_apostrophe(char c)
{
	return (c == '\'');
}

int	is_string_separator(char c)
{
	return (is_guillemet(c) || is_apostrophe(c));
}
