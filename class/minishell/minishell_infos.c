/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_infos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:28:08 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/28 02:10:21 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_infos	*get_minishell_infos(t_minishell *minishell)
{
	if (!minishell)
		return (NULL);
	return (minishell->infos);
}

void	*free_infos(t_infos *infos)
{
	if (!infos)
		return (NULL);
	if (infos->info_env)
		free_info(infos->info_env);
	if (infos->info_cmd)
		free_info(infos->info_cmd);
	if (infos->info_cmd_args)
		free_info(infos->info_cmd_args);
	if (infos->info_configured)
		free_info(infos->info_configured);
	if (infos->info_configured_args)
		free_info(infos->info_configured_args);
	free(infos);
	return (NULL);
}

t_infos	*create_minishell_infos(void)
{
	t_infos	*infos;

	infos = ft_calloc(sizeof(t_infos), 1);
	if (!infos)
		return (NULL);
	infos->info_env = create_info();
	if (!infos->info_env)
		return (free_infos(infos));
	infos->info_cmd = create_info();
	if (!infos->info_cmd)
		return (free_infos(infos));
	infos->info_cmd_args = create_info();
	if (!infos->info_cmd_args)
		return (free_infos(infos));
	infos->info_configured = create_info();
	if (!infos->info_configured)
		return (free_infos(infos));
	infos->info_configured_args = create_info();
	if (!infos->info_configured_args)
		return (free_infos(infos));
	return (infos);
}
