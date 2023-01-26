/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 17:18:44 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/16 22:46:45 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARG_H
# define ARG_H
# include "../class.h"

int		append_args(t_args **args, t_string *new_arg);
t_args	*create_args(t_args *prev, t_string *string);
char	**list_to_array(t_args *arg);
#endif
