/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:19:47 by nkarpilo          #+#    #+#             */
/*   Updated: 2023/11/13 14:22:48 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_convert_itoa(int n, int i, char *res, int sign)
{
	while (--i >= 0)
	{
		res[i] = (n % 10) + '0';
		n = n / 10;
	}
	if (sign == -1)
		res[0] = '-';
	return (res);
}

static int	numlen(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		i++;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		i;
	int		sign;

	sign = 1;
	res = NULL;
	i = numlen(n);
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (!res)
		return (res);
	res[i] = '\0';
	if (n < 0)
	{
		n *= -1;
		sign = -1;
	}
	res = ft_convert_itoa (n, i, res, sign);
	return (res);
}
