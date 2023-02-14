/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:51:49 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/11 15:57:13 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

void	go_to_home(t_env **env)
{
	t_env	*home;

	home = get_env_from_char_key(*env, "HOME", 0);
	go_to_directory(home->value, env);
}

void	go_to_directory(t_string *path, t_env **env)
{
	char	*old_pwd;
	char	*new_pwd;
	int		has_access;

	exec_pwd(0, &old_pwd, 0);
	has_access = check_access(get_string(path));
	if (chdir(get_string(path)) == -1)
		cd_print_error(has_access, path);
	change_old_pwd(env, old_pwd);
	exec_pwd(0, &new_pwd, 0);
	change_pwd(env, new_pwd);
	free(old_pwd);
	free(new_pwd);
}
