/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 21:01:44 by my_name_          #+#    #+#             */
/*   Updated: 2023/03/06 01:17:47 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../redirection.h"

void	call_heredoc(t_cmd *cmd)
{
	t_string	*line;
	t_heredoc	*heredoc;

	line = NULL;
	heredoc = cmd->heredoc;
	while (heredoc)
	{
		while (1)
		{
			line = prompt("heredoc> ", 0);
			if (!line)
				break ;
			if (equals_string(line, heredoc->file))
				break ;
			if (!heredoc->next)
				ft_putendl_fd(line->value, heredoc->fd);
			free_string(line);
		}
		if (heredoc->next)
			heredoc = heredoc->next;
		else
			break ;
	}
	free_string(line);
}

t_heredoc	*create_heredoc(t_string *filename, int fd, void *prev, void *next)
{
	t_heredoc	*heredoc;

	heredoc = ft_calloc(sizeof(t_heredoc), 1);
	if (!heredoc)
		return (NULL);
	heredoc->file = string_dup(filename);
	heredoc->fd = fd;
	heredoc->prev = prev;
	heredoc->next = next;
	return (heredoc);
}

t_heredoc	*get_last_heredoc(t_cmd *cmd)
{
	while (cmd->heredoc && ((t_heredoc *)cmd->heredoc)->next)
		cmd->heredoc = ((t_heredoc *)cmd->heredoc)->next;
	return (cmd->heredoc);
}

t_string	*get_path_name(t_string *file)
{
	t_string	*path;

	path = create_string(TMP_PATH);
	if (!path)
		return (NULL);
	append_string(&path, file);
	if (!path)
		return (NULL);
	return (path);
}

int	execute_heredoc(t_string *file)
{
	int			fd;
	t_string	*path;
	t_string	*line;

	path = get_path_name(file);
	fd = open_file(path->value, O_RDWR | O_TRUNC | O_CREAT, 0777);
	while (1)
	{
		line = prompt("> ", 0);
		if (!line || !line->value)
		{
			(free_string(path), free_string(line));
			return (-1);
		}
		if (equals_string(line, file))
		{
			free_string(line);
			break ;
		}
		(ft_putendl_fd(line->value, fd), free_string(line));
	}
	close(fd);
	fd = open_file(path->value, O_RDONLY | O_CREAT, 0777);
	free_string(path);
	return (fd);
}
