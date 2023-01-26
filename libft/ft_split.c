/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgloriod <dgloriod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:37:22 by dgloriod          #+#    #+#             */
/*   Updated: 2021/11/05 18:20:25 by dgloriod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static int	ft_get_words(char const *str, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			words++;
			while (str[i] == c)
				i++;
		}
		i++;
	}
	if (i > 0)
		words++;
	return (words);
}

static char	**ft_reset(char **result, int words)
{
	int	word;

	word = -1;
	while (++word < words)
		free(result[word]);
	free(result);
	return (0);
}

static char	**ft_set_words(char **result, char const *str, char c, int words)
{
	int		i;
	int		j;
	int		word;

	i = 0;
	j = 0;
	word = -1;
	while (++word < words)
	{
		while (str[i] != c && str[i])
			i++;
		result[word] = ft_substr(str, j, ((i - 1) - j) + 1);
		if (!result[word])
			return (ft_reset(result, words));
		while (str[i] == c && str[i])
			i++;
		j = i;
	}
	return (result);
}

char	**ft_split(char const *str, char c)
{
	char	**result;
	char	*string;
	char	set[2];
	int		words;

	if (!str)
		return (0);
	set[0] = c;
	set[1] = '\0';
	string = ft_strtrim(str, set);
	if (!string)
	{
		free(string);
		return (0);
	}
	words = ft_get_words(string, c);
	result = ft_calloc(words + 1, sizeof(char *));
	if (!result)
		return (0);
	result = ft_set_words(result, string, c, words);
	free(string);
	return (result);
}
