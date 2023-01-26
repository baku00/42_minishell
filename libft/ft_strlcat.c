/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgloriod <dgloriod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:37:22 by dgloriod          #+#    #+#             */
/*   Updated: 2021/11/04 15:19:59 by dgloriod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_return(size_t size, size_t len, const char *src)
{
	if (size < len)
		return (ft_strlen(src) + size);
	return (ft_strlen(src) + len);
}

static size_t	ft_size(size_t size, size_t len, const char *src, char *dst)
{
	size_t	i;

	i = 0;
	while (i < size - len - 1 && src[i])
	{
		dst[len + i] = src[i];
		i++;
	}
	dst[len + i] = '\0';
	return (i);
}

static size_t	ft_long(size_t size, size_t len, const char *src, char *dst)
{
	size_t	i;

	i = 0;
	while ((long long) i < (long long)(size - len - 1) && src[i])
	{
		dst[len + i] = src[i];
		i++;
	}
	dst[len + i] = '\0';
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(dst);
	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	if (size - len - 1 > size)
		i = ft_long(size, len, src, dst);
	else
		i = ft_size(size, len, src, dst);
	if (i < size || len <= size)
		dst[len + i] = '\0';
	return (ft_return(size, len, src));
}
