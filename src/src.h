/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 00:19:37 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/28 02:27:00 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SRC_H
# define SRC_H
# include <main.h>

int		check_access(char *path);
int		is_space(t_cmd **cmd, t_string **current_arg, t_string *line, int i);
int		skip_space(t_string *line, int i);
void	call_prompt(int key);
void	pass(int key);
void	use_signal(void);
#endif
