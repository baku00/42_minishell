/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:50:05 by my_name_          #+#    #+#             */
/*   Updated: 2023/03/06 00:10:22 by my_name_         ###   ########.fr       */
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

int	parser(t_parser *parser, t_env *env, t_string **current_arg, t_cmd **cmd)
{
	while (parser->i < get_string_length(parser->line))
	{
		if (is_string_separator(get_string(parser->line)[parser->i]))
		{
			if (!parse_string(env, current_arg, parser->line, &parser->i))
				return (!!free_all_cmd(*cmd) - 1);
		}
		else if (redirection(cmd, parser->line, parser->i))
			break ;
		else if (is_dollars(get_string(parser->line)[parser->i]))
			parser->i += get_dollar(parser->line, parser->i, current_arg, env);
		else if (get_string(parser->line)[parser->i] == ' ')
		{
			parser->i = is_space(cmd, current_arg, parser->line, parser->i);
			if (parser->i == -1)
				return (!!free_all_cmd(*cmd) - 1);
			continue ;
		}
		else if (!append_char(current_arg, get_string(parser->line)[parser->i]))
			return (!!free_all_cmd(*cmd) - 1);
		parser->i++;
	}
	return (parser->i);
}

t_cmd	*create_cmd(t_cmd *prev, t_string *line, int i, t_env *env)
{
	t_cmd		*cmd;
	t_string	*current_arg;
	t_parser	parser_t;

	if (!prepare_creation(&cmd, &current_arg, prev))
		return (NULL);
	i = skip_space(line, i);
	parser_t.i = i;
	parser_t.line = line;
	i = parser(&parser_t, env, &current_arg, &cmd);
	if (i == -1)
		return (NULL);
	(append_current_arg(&cmd, current_arg), free_string(current_arg));
	if (i < line->length && is_redirection(line->value[i + 1], 0))
		i++;
	if (i + 1 < line->length)
	{
		cmd->next = create_cmd(cmd, line, i + 1, env);
		if (!cmd->next)
			return (free_all_cmd(cmd));
	}
	return (cmd);
}

/*int	parser(t_minishell **mini, t_cmd **cmd, t_string **current_arg)
{
	while ((*mini)->i < get_string_length((*mini)->line))
	{
		if (is_string_separator(get_string((*mini)->line)[(*mini)->i]))
		{
			if (!parse_string((*mini)->env, current_arg,
			(*mini)->line, &(*mini)->i))
				return ((!!free_all_cmd(*cmd)) - 1);
		}
		else if (redirection(cmd, (*mini)->line, (*mini)->i))
			break ;
		else if (is_dollars(get_string((*mini)->line)[(*mini)->i]))
			(*mini)->i += get_dollar((*mini)->line, (*mini)->i,
			current_arg, (*mini)->env);
		else
		{
			if (get_string((*mini)->line)[(*mini)->i] == ' ')
			{
			(*mini)->i = is_space(cmd, current_arg, (*mini)->line, (*mini)->i);
				if ((*mini)->i == -1)
					return (!!free_all_cmd(cmd) - 1);
				continue ;
			}
		if (!append_char(current_arg, get_string((*mini)->line)[(*mini)->i]))
				return (!!free_all_cmd(cmd) - 1);
		}
		(*mini)->i++;
	}
	return (0);
}

t_cmd	*create_cmd(t_minishell *minishell, t_cmd *prev)
{
	t_cmd		*cmd;
	t_string	*current_arg;

	if (!prepare_creation(&cmd, &current_arg, prev))
		return (NULL);
	minishell->i = skip_space(minishell->line, minishell->i);
	if (parser(&minishell, &cmd, &current_arg))
		return (free_all_cmd(cmd));
	(append_current_arg(&cmd, current_arg), free_string(current_arg));
	if (minishell->i < get_string_length(minishell->line) && \
	is_redirection(get_string(minishell->line)[minishell->i + 1], 0))
		minishell->i++;
	if (minishell->i + 1 < get_string_length(minishell->line))
	{
		minishell->i += 1;
		cmd->next = create_cmd(minishell, cmd);
		if (!cmd->next)
			return (free_all_cmd(cmd));
	}
	return (cmd);
}
*/