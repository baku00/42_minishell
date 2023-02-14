/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:59:10 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/11 15:59:17 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

void	cd_print_error(int access, t_string *path_string)
{
	if (access == IS_DIR)
		printf("%s: Permission interdite\n", get_string(path_string));
	else if (access == IS_FILE)
		printf("%s: Est un fichier\n", get_string(path_string));
	else
		printf("%s: Aucun fichier ou dossier\n", get_string(path_string));
}
