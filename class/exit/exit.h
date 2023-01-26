/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 21:19:31 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/16 23:13:50 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H
# include "../class.h"

t_exit	g_exit_manager;
void		create_exit_manager(void);
void		set_have_to_exit(int state);
int			have_to_exit(void);
t_string	*get_exit_string(void);
void		clear_exit_manager(void);
#endif
