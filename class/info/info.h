/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 22:13:40 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/28 02:07:16 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INFO_H
# define INFO_H
# include "../class.h"

t_info	*create_info(void);
void	update_info(t_info *info, void *first, void *last);
t_info	*get_info(void *list);
void	*get_info_first(void *list);
void	*get_info_last(void *list);
int		get_info_length(void *list);
void	make_info(t_cmd *cmd, t_info *info_cmd, t_info *info_args);
void	make_info_args(t_args *arg, t_info *info_arg);
void	free_info(t_info *info);
#endif
