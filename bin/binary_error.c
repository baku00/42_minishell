/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:51:08 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/07 19:00:04 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary.h"

void	print_binary_not_found(t_string *bin)
{
	ft_putstr_fd("Erreur: la commande '", STDERR_FILENO);
	ft_putstr_fd(bin->value, STDERR_FILENO);
	ft_putendl_fd("' est introuvable", STDERR_FILENO);
}

void	print_binary_execution_error(t_string *bin)
{
	ft_putstr_fd(bin->value, STDERR_FILENO);
	perror(": Erreur d'éxecution");
}

void	print_binary_not_permission(t_string *bin)
{
	ft_putstr_fd(bin->value, STDERR_FILENO);
	ft_putendl_fd(": permission denied", STDERR_FILENO);
}
