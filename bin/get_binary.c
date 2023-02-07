/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_binary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 02:05:42 by my_name_          #+#    #+#             */
/*   Updated: 2023/02/07 00:30:37 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary.h"

char	*get_bin_path(char *bin, t_env *env)
{
	char	**paths;
	char	*path;
	int		i;
	t_env	*env_from_char;

	if (bin[0] == '/' || (bin[0] == '.' && bin[1] == '/'))
	{
		if (check_access(bin) != IS_FILE)
			return (NULL);
		else
			return (bin);
	}
	env_from_char = get_env_from_char_key(env, "PATH", 0);
	paths = ft_split(get_string(env_from_char->value), ':');
	i = -1;
	while (paths[++i])
	{
		path = ft_strdup(paths[i]);
		free(paths[i]);
		path = ft_strjoin(path, "/");
		path = ft_strjoin(path, bin);
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
