/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:50:05 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/28 02:12:35 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int	append_full_args(t_args **args, t_string **current_arg)
{
	append_args(args, *current_arg);
	free_string(*current_arg);
	*current_arg = create_string("");
	return (!!(*current_arg));
}

void	append_current_arg(t_cmd **cmd, t_string *args)
{
	if (args->length)
	{
		if (!(*cmd)->bin)
			(*cmd)->bin = string_dup(args);
		append_args(&(*cmd)->args, args);
	}
}

t_cmd	*init_cmd(t_cmd *prev)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
	{
		set_have_to_exit(1);
		return (NULL);
	}
	cmd->bin = NULL;
	cmd->args = NULL;
	cmd->type = TYPE_CMD;
	cmd->pid = 0;
	cmd->fd_in = STDIN_FILENO;
	cmd->is_file = 0;
	cmd->fd_out = STDOUT_FILENO;
	cmd->error_id = 0;
	cmd->redirection_id = 0;
	cmd->info = NULL;
	cmd->next = NULL;
	cmd->prev = prev;
	return (cmd);
}

int	prepare_creation(t_cmd **cmd, t_string **current_arg, t_cmd *prev)
{
	*cmd = init_cmd(prev);
	if (!*cmd)
		return (0);
	*current_arg = create_string("");
	if (!*current_arg)
	{
		free_all_cmd(*cmd);
		return (0);
	}
	return (1);
}

t_cmd	*create_cmd(t_cmd *prev, t_string *line, int i, t_env *env)
{
	t_cmd		*cmd;
	t_string	*current_arg;

	if (!prepare_creation(&cmd, &current_arg, prev))
		return (NULL);
	i = skip_space(line, i);
	while (i < line->length)
	{
		if (is_string_separator(line->value[i]))
		{
			if (!parse_string(env, &current_arg, line, &i))
				return (NULL);
		}
		else if (is_redirection(line->value[i], line->value[i + 1]))
		{
			cmd->redirection_id = redirection_id(line->value[i], \
			line->value[i + 1]);
			break ;
		}
		else if (is_dollars(line->value[i]))
			i += get_dollar(line, i, &current_arg, env);
		else
		{
			if (line->value[i] == ' ')
			{
				i = is_space(&cmd, &current_arg, line, i);
				if (i == -1)
					return (NULL);
				continue ;
			}
			append_char(&current_arg, line->value[i]);
		}
		i++;
	}
	(append_current_arg(&cmd, current_arg), free_string(current_arg));
	if (i < line->length && is_redirection(line->value[i + 1], 0))
		i++;
	if (i + 1 < line->length)
		cmd->next = create_cmd(cmd, line, i + 1, env);
	return (cmd);
}
