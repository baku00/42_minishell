/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 00:13:18 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/11 16:02:57 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H
# define CD_H
# include "../builtins.h"

void	exec_cd(t_args *path, t_env **env);
void	cd_print_error(int access, t_string *path_string);
void	go_to_home(t_env **env);
void	go_to_directory(t_string *path, t_env **env);
int		check_path(t_args **path, t_env **env);
#endif
