/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 22:13:40 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/16 22:47:32 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INFO_H
# define INFO_H
# include "../class.h"

t_info	create_info(void *first, void *last);
void	update_info(t_info *info, void *first, void *last);
t_info	*get_info(void *list);
void	*get_info_first(void *list);
void	*get_info_last(void *list);
int		get_info_length(void *list);
#endif
