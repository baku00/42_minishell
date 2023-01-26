/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgloriod <dgloriod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:37:22 by dgloriod          #+#    #+#             */
/*   Updated: 2021/11/02 16:38:58 by dgloriod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dest;
	unsigned char		*source;

	dest = (unsigned char *) dst;
	source = (unsigned char *) src;
	if (dst > src)
	{
		while (len--)
		{
			dest[len] = source[len];
		}
	}
	else
		dest = ft_memcpy(dst, src, len);
	return ((void *) dest);
}
