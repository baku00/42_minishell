/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:24:53 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/02 19:57:50 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../class.h"

t_minishell	*create_minishell(void);
t_infos		*get_minishell_infos(t_minishell *minishell);
t_info		*get_minishell_info_env(t_minishell *minishell);
t_info		*get_minishell_info_cmd(t_minishell *minishell);
t_info		*get_minishell_info_cmd_args(t_minishell *minishell);
t_info		*get_minishell_info_configured(t_minishell *minishell);
t_info		*get_minishell_info_configured_args(t_minishell *minishell);
void		*free_minishell(t_minishell *minishell);
t_infos		*create_minishell_infos(void);
void		*free_infos(t_infos *infos);
t_cmd		*get_minishell_cmd(t_minishell *minishell);
t_cmd		*get_minishell_configured(t_minishell *minishell);
t_args		*get_minishell_cmd_args(t_minishell *minishell);
t_args		*get_minishell_configured_args(t_minishell *minishell);
void		*reset_minishell(t_minishell *minishell);
#endif