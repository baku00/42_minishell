/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 00:14:14 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/29 00:55:36 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

static void	check_path(t_args **path, t_env **env)
{
	if (!(*path))
		*path = \
		create_args(NULL, get_env_from_char_key(*env, "HOME", 0)->value);
	else if (!(*path)->string)
		(*path)->string = get_env_from_char_key(*env, "HOME", 0)->value;
	else if (!get_string_length((*path)->string))
		(*path)->string = get_env_from_char_key(*env, "HOME", 0)->value;
}

static void	cd_print_error(int access, t_string *path_string)
{
	if (access == IS_DIR)
		printf("%s: Permission interdite\n", get_string(path_string));
	else if (access == IS_FILE)
		printf("%s: Est un fichier\n", get_string(path_string));
	else
		printf("%s: Aucun fichier ou dossier\n", get_string(path_string));
}

void	exec_cd(t_args *path, t_env **env)
{
	int			has_access;
	t_string	*path_string;
	char		*char_path;
	int			path_is_null;

	(void)env;
	path_is_null = !path;
	*env = get_info_first(*env);
	check_path(&path, env);
	exec_pwd(0, &char_path, STDOUT_FILENO);
	path_string = string_dup(path->string);
	has_access = check_access(get_string(path_string));
	if (chdir(get_string(path_string)) == -1)
		cd_print_error(has_access, path_string);
	else
	{
		free_string(path_string);
		path_string = NULL;
		change_pwd(env, path_string, char_path, "OLDPWD=");
		char_path = NULL;
		exec_pwd(0, &char_path, STDOUT_FILENO);
		path_string = NULL;
		change_pwd(env, path_string, char_path, "PWD=");
		free_string(path_string);
	}
	if (path_is_null)
		free_args(path);
}

// free_string(path_string);
// path_string = create_string(char_path);
// append_front_string(&path_string, create_string("OLDPWD="));
// append_var(env, path_string);

// char_path = NULL;
// exec_pwd(0, &char_path, STDOUT_FILENO);

// free_string(path_string);
// path_string = create_string(char_path);
// append_front_string(&path_string, create_string("PWD="));
// append_var(env, path_string);