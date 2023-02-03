/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 23:00:53 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/03 16:33:10 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H
# include "../class.h"
# define REDIRECTION_PIPE 1
# define REDIRECTION_INPUT 2
# define REDIRECTION_OUTPUT 3
# define REDIRECTION_HEREDOC 4
# define REDIRECTION_APPEND 5
# define REDIRECTION_EMPTY 6
# define REDIRECTION_ERROR -7
# define REDIRECTION_NOT_EXIST -7

int		is_pipe(char c);
int		is_input(char c);
int		is_output(char c);
int		is_heredoc(char c, char c2);
int		is_append(char c, char c2);
int		is_redirection(char c, char c2);
int		redirection_id(char c, char c2);
int		redirect_fd(t_cmd **cmd);
void	execute_fd(t_cmd *cmd);
void	close_fd(int fd, int std);
int		is_redirection_out(int r_id);
int		is_redirection_in(int r_id);
t_cmd	*make_redirection(t_cmd *prev, t_cmd *cmd, int *success);
int		is_redirection_in_or_out(int r_id);
int		is_redirection_pipe(int r_id);
char	*get_redirection_from_id(int r_id);
void	print_redirection_error(int error);
void	print_error_redirection(t_cmd *cmd_error);
int		is_redirection_input(int r_id);
int		is_redirection_heredoc(int r_id);
int		is_redirection_in(int r_id);
int		is_redirection_output(int r_id);
int		is_redirection_append(int r_id);
int		is_redirection_out(int r_id);
void	call_heredoc(t_cmd *cmd);
#endif
