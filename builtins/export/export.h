/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 03:48:49 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/16 22:57:51 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H
# include "../builtins.h"
# define KEY_EMPTY 1
# define KEY_INVALID 2

void	print_export(t_env *env, int fd);
void	exec_export(t_cmd *cmd, t_env *env);
int		append_var(t_env **env, t_string *args);
#endif