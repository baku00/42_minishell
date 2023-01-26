/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgloriod <dgloriod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:37:22 by dgloriod          #+#    #+#             */
/*   Updated: 2021/10/29 15:17:45 by dgloriod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_intlen(int nbr)
{
	long int	n;
	long int	nb;
	int			l;

	n = 1;
	l = 1;
	nb = nbr;
	if (nb < 0)
	{
		nb *= -1;
		l++;
	}
	if (nb < 10)
		return (l);
	while (n < nb)
	{
		n *= 10;
		l++;
	}
	if (n > nb)
	{
		n /= 10;
		l--;
	}
	return (l);
}

static void	ft_strcpy(char *dst, char *str)
{
	while (*str)
		*dst++ = *str++;
}

char	*ft_itoa(int nbr)
{
	char		*result;
	int			ilen;
	long int	nb;

	ilen = ft_intlen(nbr) - 1;
	result = ft_calloc(ilen + 2, sizeof(char));
	if (!result)
		return (0);
	nb = nbr;
	if (nb == 0 || nb == -2147483648)
	{
		result[0] = '0';
		if (nb == -2147483648)
			ft_strcpy(result, "-2147483648");
		return (result);
	}
	if (nb < 0)
		nb *= -1;
	result[0] = '-';
	while (nb > 0)
	{
		result[ilen--] = (char)(nb % 10) + 48;
		nb /= 10;
	}
	return (result);
}
