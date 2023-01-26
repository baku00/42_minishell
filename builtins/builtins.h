/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 21:00:12 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/16 22:47:18 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "../header/includes.h"
# include "env/env.h"
# include "pwd/pwd.h"
# include "export/export.h"
# include "unset/unset.h"
# include "cd/cd.h"
# include "echo/echo.h"
# define ECHO_CMD 1
# define CD 2
# define PWD 3
# define EXPORT 4
# define UNSET 5
# define ENV 6
# define EXIT 7

int		is_builtins(t_string *cmd);
void	exec_builtins(t_cmd *cmd, t_env *env);
#endif
