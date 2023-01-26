/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:13:13 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/26 17:18:09 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

void	print_redirection_error(int error)
{
	printf ("Erreur de redirection: ");
	if (error == IS_DIR)
		printf("Le fichier est un dossier\n");
	else if (error == REDIRECTION_ERROR)
		printf("Une erreur interne est survenu\n");
	else
		printf("%d\n", error);
}