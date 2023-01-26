/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:48:45 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/16 22:47:23 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOLLARS_H
# define DOLLARS_H
# include "../class.h"

int			is_dollars(char c);
t_string	*get_variable_name(t_string *string, int i);
t_string	*check_for_variable(t_string *string);
void		replace_all_variables(t_env *env, t_string **string);
#endif
