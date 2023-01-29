/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 18:25:49 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/28 19:50:17 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include "header/header.h"

int		main(int argc, char **argv, char **envp);
void	execute(void *minishell, void *line, void *env);
void	free_all(void);
#endif
