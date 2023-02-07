/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 21:01:44 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/07 02:52:26 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../redirection.h"

void	call_heredoc(t_cmd *cmd)
{
	t_string	*line;

	line = NULL;
	while (1)
	{
		line = prompt("heredoc> ");
		if (!line)
			break ;
		if (equals_string(line, cmd->heredoc_file))
			break ;
		ft_putendl_fd(line->value, cmd->fd_in);
		free_string(line);
	}
	free_string(line);
}
