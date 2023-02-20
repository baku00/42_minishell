/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:50:12 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/16 23:26:03 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H
# include "../class.h"

int		append_full_args(t_args **args, t_string **current_arg);
void	append_current_arg(t_cmd **cmd, t_string *args);
t_cmd	*init_cmd(t_cmd *prev);
t_cmd	*create_cmd(t_cmd *prev, t_string *line, int i, t_env *env);
t_cmd	*check_error(t_cmd *cmd);
void	*free_all_cmd(void *cmd);
void	free_cmd(t_cmd	*cmd);
void	*free_null_cmd(t_cmd *cmd);
t_cmd	*cmd_dup(t_cmd *prev, t_cmd *cmd);
t_cmd	*get_cmd_prev(t_cmd *cmd);
t_cmd	*get_cmd_next(t_cmd *cmd);
t_args	*get_cmd_args(t_cmd *cmd);
int		get_cmd_redirection_id(t_cmd *cmd);
int		redirection(t_cmd **cmd, t_string *line, int i);
#endif