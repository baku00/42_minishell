/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 00:14:14 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/16 23:10:02 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

static void	cd_error(void)
{
	printf("usage: cd <path>\n");
}

void	exec_cd(t_args *path, t_env **env)
{
	int			success;
	int			has_access;
	t_string	*path_string;

	(void)env;
	if (!path || path->next || !path->string)
		return (cd_error());
	path_string = string_dup(path->string);
	has_access = check_access(get_string(path_string));
	success = chdir(get_string(path_string));
	if (success == -1 && has_access == IS_DIR)
		printf("%s: Permission interdite\n", get_string(path_string));
	else if (success == -1 && has_access == IS_FILE)
		printf("%s: Est un fichier\n", get_string(path_string));
	else if (success == -1)
		printf("%s: Aucun fichier ou dossier\n", get_string(path_string));
}
