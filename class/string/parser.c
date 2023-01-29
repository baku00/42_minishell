/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 01:56:25 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/28 02:00:04 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

void	*parse_error(int parse_string)
{
	if (parse_string == ERROR_NOT_CLOSE_QUOTE)
		ft_putstr_fd("Guillement ou apostrophe non fermé\n", STDERR_FILENO);
	return (NULL);
}

int	parse_string(t_env *env, t_string **current_arg, t_string *line, int *i)
{
	int	parse;

	parse = parse_string_separator(env, current_arg, line, i);
	if (parse != SUCCESS)
	{
		free_string(*current_arg);
		parse_error(parse);
	}
	return (parse == SUCCESS);
}

int	parse_string_separator(t_env *env, t_string **cmd, t_string *line, int *i)
{
	t_string	*extracted;

	extracted = extract_string_into(line->value, line->value[*i], i);
	if (!extracted)
		return (ERROR_MEMORY);
	if (!line->value[*i])
		return (ERROR_NOT_CLOSE_QUOTE);
	if (is_guillemet(line->value[*i]))
		replace_all_variables(env, &extracted);
	append_string(cmd, extracted);
	free_string(extracted);
	return (SUCCESS);
}
