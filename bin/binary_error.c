/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:51:08 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/12 02:03:31 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary.h"

void	print_binary_not_found(t_string *bin)
{
	ft_putstr_fd("Erreur: la commande '", STDERR_FILENO);
	ft_putstr_fd(bin->value, STDERR_FILENO);
	ft_putendl_fd("' est introuvable", STDERR_FILENO);
}

void	print_binary_execution_error(t_string *bin)
{
	ft_putstr_fd(bin->value, STDERR_FILENO);
	perror(": Erreur d'éxecution");
}

void	print_binary_not_permission(t_string *bin)
{
	ft_putstr_fd(bin->value, STDERR_FILENO);
	ft_putendl_fd(": permission denied", STDERR_FILENO);
}

void	binary_error(char *path, t_cmd *cmd, char **args, char **env_vars)
{
	int	i;

	print_binary_execution_error(cmd->bin);
	if (path)
	{
		free(path);
	}
	i = -1;
	if (args)
	{
		while (args[++i])
			free(args[i]);
		free(args);
	}
	i = -1;
	if (env_vars)
	{
		while (env_vars[++i])
			free(env_vars[i]);
		free(env_vars);
	}
}

void	print_binary_type_error(t_string *bin, int type)
{
	ft_putstr_fd("Erreur: ", STDERR_FILENO);
	ft_putstr_fd(get_string(bin), STDERR_FILENO);
	if (type == IS_DIR)
		ft_putendl_fd(" est un dossier", STDERR_FILENO);
	else
		ft_putendl_fd(" n'a pas été trouvé", STDERR_FILENO);
}
