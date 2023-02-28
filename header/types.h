/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 16:18:32 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/23 21:57:02 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H
# include "header.h"
# define TYPE_ENV 1
# define TYPE_CMD 2
# define TYPE_FILE 3
# define TYPE_ARG 4

int	g_status;

typedef struct s_info
{
	int		length;
	void	*first;
	void	*last;
}	t_info;

typedef struct s_infos
{
	t_info	*info_env;
	t_info	*info_cmd;
	t_info	*info_cmd_args;
	t_info	*info_configured;
	t_info	*info_configured_args;
}	t_infos;

typedef struct s_string
{
	char	*value;
	int		length;
	int		error;
}	t_string;

typedef struct s_exit
{
	int			have_to_exit;
	t_string	*string;
}	t_exit;

typedef struct s_args
{
	t_string	*string;
	int			type;
	void		*info;
	void		*next;
	void		*prev;
}	t_args;

typedef struct s_heredoc
{
	t_string	*file;
	int			fd;
	void		*prev;
	void		*next;
}	t_heredoc;

typedef struct s_cmd
{
	t_string	*bin;
	t_args		*args;
	t_heredoc	*heredoc;
	int			pid;
	int			redirection_id;
	int			type;
	int			is_file;
	int			fd_in;
	int			fd_out;
	int			error_id;
	void		*info;
	void		*next;
	void		*prev;
}	t_cmd;

typedef struct s_env
{
	t_string		*key;
	t_string		*value;
	struct s_env	*sorted;
	int				type;
	int				has_value;
	int				index;
	void			*info;
	void			*next;
	void			*prev;
}	t_env;

typedef struct s_parser
{
	int			i;
	t_string	*line;
}	t_parser;

typedef struct s_config
{
	int	exit;
}	t_config;

typedef struct s_minishell
{
	t_env		*env;
	t_cmd		*cmd;
	t_cmd		*configured;
	t_config	*config;
	t_infos		*infos;
	t_string	*line;
	int			*fd;
	int			i;
}	t_minishell;

void	args_free_all(t_args *args);
void	free_args(t_args *args);
void	cmd_free_all(t_cmd *cmd);

#endif
