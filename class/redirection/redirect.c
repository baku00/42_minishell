/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 19:03:52 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/13 23:11:07 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

static int	redirect_pipe(t_cmd **cmd)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (REDIRECTION_ERROR);
	(*cmd)->fd_out = fd[1];
	((t_cmd *)(*cmd)->next)->fd_in = fd[0];
	return (1);
}

int	redirect_fd(t_cmd **cmd)
{
	t_cmd	*next;
	char	*file;

	if (!(*cmd)->next)
		return (REDIRECTION_EMPTY);
	next = (*cmd)->next;
	file = get_string(next->bin);
	if ((*cmd)->redirection_id == REDIRECTION_OUTPUT)
		(*cmd)->fd_out = open_file(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	else if ((*cmd)->redirection_id == REDIRECTION_APPEND)
		(*cmd)->fd_out = open_file(file, O_WRONLY | O_APPEND | O_CREAT, 0777);
	else if ((*cmd)->redirection_id == REDIRECTION_INPUT)
		(*cmd)->fd_in = open_file(file, O_RDONLY, -1);
	else if ((*cmd)->redirection_id == REDIRECTION_HEREDOC)
	{
		(*cmd)->fd_in = open_file(file, O_RDWR | O_TRUNC | O_CREAT, 0777);
		(*cmd)->heredoc_file = string_dup(next->bin);
	}
	else if ((*cmd)->redirection_id == REDIRECTION_PIPE)
		redirect_pipe(cmd);
	if ((*cmd)->fd_in < 0)
		return ((*cmd)->fd_in);
	else if ((*cmd)->fd_out < 0)
		return ((*cmd)->fd_out);
	return (1);
}

void	append_more_args(t_args **args, t_args *append)
{
	if (!append || !(*args))
		return ;
	while ((*args)->next)
		*args = (*args)->next;
	(*args)->next = args_dup((*args), append);
	while ((*args)->prev)
		(*args) = (*args)->prev;
}

static void	*free_to_first(t_cmd **configured)
{
	while ((*configured)->prev)
	{
		(*configured) = (*configured)->prev;
		free_cmd((*configured)->next);
	}
	return (free_null_cmd((*configured)));
}

t_cmd	*make_redirection(t_cmd *prev, t_cmd *cmd, int *success)
{
	t_cmd	*configured;

	configured = cmd_dup(prev, cmd);
	if (!configured)
		return (free_null_cmd(configured));
	if (!is_redirection_pipe(cmd->redirection_id))
	{
		if (!create_redirection(&configured, &cmd, success))
			return (free_null_cmd(configured));
		copy_fd_in_and_out(&configured, cmd);
		if (cmd->prev && \
		!is_redirection_pipe(get_cmd_prev(cmd)->redirection_id))
			copy_fd_in_and_out(&configured, cmd->prev);
	}
	if (cmd->next)
	{
		if (!create_redirection_pipe(&configured, &cmd))
			return (free_to_first(&configured));
		configured->next = make_redirection(configured, cmd->next, success);
		if (!configured->next)
			return (free_to_first(&configured));
	}
	return (configured);
}

// t_cmd	*make_redirection(t_cmd *prev, t_cmd *cmd, int *success)
// {
// 	t_cmd	*configured;

// 	configured = cmd_dup(prev, cmd);
// 	if (!configured)
// 		return (free_null_cmd(configured));
// 	if (!is_redirection_pipe(cmd->redirection_id))
// 	{
// 		while (is_redirection_in_or_out(cmd->redirection_id))
// 		{
// 			if (cmd->prev && cmd->redirection_id == 
// get_cmd_prev(cmd)->redirection_id)
// 				close_cmd_fd(cmd->prev);
// 			*success = redirect_fd(&cmd);
// 			if (*success != 1)
// 				return (free_null_cmd(configured));
// 			if (is_redirection_heredoc(cmd->redirection_id))
// 				configured->heredoc_file = string_dup(cmd->heredoc_file);
// 			if (cmd->prev && 
// get_cmd_prev(cmd)->redirection_id != REDIRECTION_PIPE && cmd->args)
// 				append_more_args(&configured->args, get_cmd_args(cmd)->next);
// 			if (cmd->next)
// 				cmd = cmd->next;
// 			else
// 				break ;
// 		}
// 		copy_fd_in_and_out(&configured, cmd);
//	if (cmd->prev && !is_redirection_pipe(get_cmd_prev(cmd)->redirection_id))
// 			copy_fd_in_and_out(&configured, cmd->prev);
// 	}
// 	if (cmd->next)
// 	{
// 		if (!create_redirection_pipe(&configured, &cmd))
// 			return (free_to_first(&configured));
// 		configured->next = make_redirection(configured, cmd->next, success);
// 		if (!configured->next)
// 			return (free_to_first(&configured));
// 	}
// 	return (configured);
// }
