/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_includes.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:20:38 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/13 01:39:14 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_INCLUDES_H
# define MAIN_INCLUDES_H
# include "header/includes.h"

void		execute(t_minishell *minishell, t_string *line, t_env **env);
#endif