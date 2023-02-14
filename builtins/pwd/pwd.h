/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 21:43:10 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/11 15:44:45 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PWD_H
# define PWD_H
# include "../builtins.h"
# define OLDPWD_TYPE 1
# define PWD_TYPE 2

void	change_old_pwd(t_env **env, char *old_path);
void	change_pwd(t_env **env, char *path);
void	exec_pwd(int display, char **path, int fd);
void	exec_change_pwd(t_env **env, char *path, int type);
#endif
