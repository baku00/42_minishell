/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 18:28:19 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/22 23:40:23 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_H
# define BINARY_H
# include "../header/includes.h"

char		*get_bin_path(char *bin, t_env *env);
void		exec_binary(char *path, t_cmd *cmd, t_env *env);
void		exec_bin(t_cmd *cmd, t_env **env);
t_string	*prompt(char *display, int save_history);
void		print_binary_not_found(t_string *bin);
void		print_binary_execution_error(t_string *bin);
void		print_binary_not_permission(t_string *bin);
void		binary_error(char *path, t_cmd *cmd, char **args, char **env_vars);
void		print_binary_type_error(t_string *bin, int type);
#endif
