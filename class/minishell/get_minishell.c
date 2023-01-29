/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:26:17 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/28 02:10:41 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*get_minishell_env(t_minishell *minishell)
{
	if (!minishell)
		return (NULL);
	return (minishell->env);
}

t_cmd	*get_minishell_cmd(t_minishell *minishell)
{
	if (!minishell)
		return (NULL);
	return (minishell->cmd);
}

t_args	*get_minishell_cmd_args(t_minishell *minishell)
{
	if (!minishell)
		return (NULL);
	return (get_minishell_cmd(minishell)->args);
}

t_cmd	*get_minishell_configured(t_minishell *minishell)
{
	if (!minishell)
		return (NULL);
	return (minishell->configured);
}

t_args	*get_minishell_configured_args(t_minishell *minishell)
{
	if (!minishell)
		return (NULL);
	return (get_minishell_configured(minishell)->args);
}
