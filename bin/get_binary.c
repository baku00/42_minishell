/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_binary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:05:42 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/12 16:09:33 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary.h"

static char	*check_relative_or_absolute_path(char *bin)
{
	int	length;

	length = ft_strlen(bin);
	if (bin[0] == '/')
		return (bin);
	else if (length >= 2 && bin[0] == '.' && bin[1] == '/')
		return (bin);
	else if (length >= 3 && bin[0] == '.' && bin[1] == '.' && bin[2] == '/')
		return (bin);
	return (0);
}

char	*create_path(char *path, char *bin)
{
	char	*created;

	created = ft_strdup(path);
	created = ft_strjoin(created, "/");
	created = ft_strjoin(created, bin);
	return (created);
}

char	*get_path(char *bin, char **paths)
{
	char	*path;
	int		i;

	i = -1;
	while (paths[++i])
	{
		path = create_path(paths[i], bin);
		free(paths[i]);
		if (check_access(path) == IS_FILE)
		{
			while (paths[++i])
				free(paths[i]);
			free(paths);
			return (path);
		}
		free(path);
	}
	free(paths);
	return (NULL);
}

char	*get_bin_path(char *bin, t_env *env)
{
	char	**paths;
	char	*path;
	t_env	*env_from_char;

	if (check_relative_or_absolute_path(bin))
		return (bin);
	env_from_char = get_env_from_char_key(env, "PATH", 0);
	if (!env_from_char)
		return (NULL);
	paths = ft_split(get_string(env_from_char->value), ':');
	path = get_path(bin, paths);
	return (path);
}
