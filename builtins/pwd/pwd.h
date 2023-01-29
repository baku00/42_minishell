/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 21:43:10 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/28 16:33:48 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PWD_H
# define PWD_H
# include "../builtins.h"

void	change_pwd(t_env **env, t_string *paths, char *charp, char *pwd_type);
void	exec_pwd(int display, char **path, int fd);
#endif
