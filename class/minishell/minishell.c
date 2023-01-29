/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:23:35 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/28 02:10:58 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_minishell(t_minishell *minishell)
{
	if (!minishell)
		return (NULL);
	if (minishell->env)
		free_all_env(minishell->env);
	if (minishell->cmd)
		free_all_cmd(minishell->cmd);
	if (minishell->configured)
		free_all_cmd(minishell->configured);
	if (minishell->infos)
		free_infos(minishell->infos);
	if (minishell->line != NULL)
		free_string(minishell->line);
	free(minishell);
	return (NULL);
}

t_minishell	*create_minishell(void)
{
	t_minishell	*minishell;

	minishell = ft_calloc(sizeof(t_minishell), 1);
	if (!minishell)
		return (NULL);
	minishell->env = NULL;
	minishell->cmd = NULL;
	minishell->configured = NULL;
	minishell->config = NULL;
	minishell->infos = create_minishell_infos();
	if (!minishell->infos)
		return (free_minishell(minishell));
	return (minishell);
}
