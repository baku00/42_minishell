/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:25:04 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/30 16:25:49 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unset.h"

void	print_invalid_params(t_string *param)
{
	ft_putstr_fd("Parametre invalide: ", STDERR_FILENO);
	ft_putendl_fd(get_string(param), STDERR_FILENO);
}
