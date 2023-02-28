/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 01:37:26 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/28 03:17:02 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
# define FILE_H
# include "../class.h"

int		open_file(char *path, int flags, int access_level);
void	close_cmd_fd(t_cmd *cmd);
void	close_all_fd(t_cmd *cmd);
void	copy_fd_in_and_out(t_cmd **configured, t_cmd *cmd);
void	clear_tmp_dir(void);
#endif