/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgloriod <dgloriod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:37:22 by dgloriod          #+#    #+#             */
/*   Updated: 2021/10/21 14:53:54 by dgloriod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *) s;
	i = ft_strlen(s) - 1;
	if (c == 0)
		return (str + ft_strlen(str));
	while (i >= 0 && str[i])
	{
		if ((char) str[i] == (char) c)
			return (&str[i]);
		i--;
	}
	if (s[i] == c)
		return (&str[i]);
	return (0);
}
