/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:08:21 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/04/05 20:25:53 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_print_hex(unsigned long n, const char format, int total)
{
	const char	*base;
	int			error;

	if (format == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (n >= 16)
		total = ft_print_hex(n / 16, format, total);
	if (total < 0)
		return (-1);
	error = write (1, &base[n % 16], 1);
	if (error < 0)
		return (-1);
	return (total + 1);
}
