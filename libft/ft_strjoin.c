/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: my_name_ <my_name_@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:37:22 by dgloriod          #+#    #+#             */
/*   Updated: 2023/01/27 16:15:06 by my_name_         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	if (!s1 || !s2)
		return (0);
	str = ft_calloc(ft_strlen((char *) s1) + \
			ft_strlen((char *) s2) + 1, sizeof(char));
	if (!str)
		return (0);
	i = 0;
	while (str[i])
		str[i++] = '\0';
	i = 0;
	j = 0;
	len = ft_strlen(s1);
	while (i < len)
		str[j++] = s1[i++];
	i = 0;
	len = ft_strlen(s2);
	while (i < len)
		str[j++] = s2[i++];
	free(s1);
	return (str);
}
