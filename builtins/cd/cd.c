/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 00:14:14 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/11 16:09:22 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

void	exec_cd(t_args *path, t_env **env)
{
	if (check_path(&path, env))
	{
		go_to_home(env);
		free_args(path);
	}
	else
		go_to_directory(path->string, env);
}

/*
void	exec_cd(t_args *path, t_env **env)
{
	int			has_access;
	t_string	*path_string;
	char		*char_path;
	int			path_is_null;

	path_is_null = !path;
	*env = get_info_first(*env);
	check_path(&path, env);
	exec_pwd(0, &char_path, STDOUT_FILENO);
	path_string = string_dup(path->string);
	has_access = check_access(get_string(path_string));
	if (chdir(get_string(path_string)) == -1)
	{
		cd_print_error(has_access, path_string);
		free(char_path);
	}
	else
	{
		free_string(path_string);
		path_string = NULL;
		change_pwd(env, path_string, char_path, "OLDPWD=");
		char_path = NULL;
		exec_pwd(0, &char_path, STDOUT_FILENO);
		path_string = NULL;
		change_pwd(env, path_string, char_path, "PWD=");
	}
	if (path_is_null)
		free_args(path);
	free_string(path_string);
}*/

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