/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:13:13 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/30 21:15:49 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

void	print_error_redirection(t_cmd *cmd_error)
{
	char	*redirection_error;

	redirection_error = get_redirection_from_id(cmd_error->redirection_id);
	ft_putstr_fd("Erreur de syntaxe ", STDERR_FILENO);
	ft_putstr_fd("près du symbole inattendu: '", STDERR_FILENO);
	ft_putstr_fd(redirection_error, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	free(redirection_error);
}

void	print_redirection_error(int error)
{
	ft_putstr_fd("Erreur de redirection", STDERR_FILENO);
	if (error == IS_DIR)
		ft_putendl_fd(": Le fichier est un dossier", STDERR_FILENO);
	else if (error == REDIRECTION_ERROR)
	{
		ft_putstr_fd(": Une erreur est survenue", STDERR_FILENO);
		ft_putendl_fd(" lors de l'ouverture du fichier", STDERR_FILENO);
	}
	ft_putendl_fd("", STDERR_FILENO);
}
