/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 22:32:38 by my_name_          #+#    #+#             */
/*   Updated: 2023/01/02 01:04:29 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

static void	init_vars(char **str1, char **str2)
{
	*str1 = NULL;
	*str2 = NULL;
}

static void	*free_vars(char **str1, char **str2)
{
	if (*str1)
		free(*str1);
	if (*str2)
		free(*str2);
	return (NULL);
}

static char	*join_all(char *before, char *handle, char *after)
{
	char	*str;

	str = ft_strdup(before);
	if (!str)
		return (NULL);
	str = ft_strjoin(str, handle);
	if (!str)
		return (NULL);
	str = ft_strjoin(str, after);
	if (!str)
		return (NULL);
	return (str);
}

static int	replace(char **str, char *needed, char *handle, int i)
{
	char	*before;
	char	*after;
	int		length;

	init_vars(&before, &after);
	before = ft_substr(*str, 0, i);
	if (!before)
		return (!!free_vars(&before, &after));
	length = ft_strlen(*str) - ft_strlen(needed) - ft_strlen(before);
	after = ft_substr(*str, i + ft_strlen(needed), length);
	if (!after)
		return (!!free_vars(&before, &after));
	free((*str));
	*str = join_all(before, handle, after);
	if (!*str)
		return (!!free_vars(&before, &after));
	return (ft_strlen(handle));
}

int	str_replace(char **str, char *needed, char *handle)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (ft_strlen(*str) == 1 || ft_strlen(*str) < ft_strlen(needed))
		return (1);
	while ((*str)[i])
	{
		j = 0;
		while ((*str)[j + i] && needed[j] && (*str)[j + i] == needed[j])
			j++;
		if (j == ft_strlen(needed))
			i += replace(str, needed, handle, i);
		else
			i++;
	}
	return (1);
}
