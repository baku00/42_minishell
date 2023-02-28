/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_minishell_info.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:28:08 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/23 22:10:51 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_info	*get_minishell_info_env(t_minishell *minishell)
{
	if (!minishell)
		return (NULL);
	return (get_minishell_infos(minishell)->info_env);
}

t_info	*get_minf_cmd(t_minishell *minishell)
{
	if (!minishell)
		return (NULL);
	return (get_minishell_infos(minishell)->info_cmd);
}

t_info	*get_minishell_info_cmd_args(t_minishell *minishell)
{
	if (!minishell)
		return (NULL);
	return (get_minishell_infos(minishell)->info_cmd_args);
}

t_info	*get_minishell_info_configured(t_minishell *minishell)
{
	if (!minishell)
		return (NULL);
	return (get_minishell_infos(minishell)->info_configured);
}

t_info	*get_minishell_info_configured_args(t_minishell *minishell)
{
	if (!minishell)
		return (NULL);
	return (get_minishell_infos(minishell)->info_configured_args);
}
