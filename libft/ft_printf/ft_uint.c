/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uint.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:55:54 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/04/05 20:26:05 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_print_uint(unsigned int n, int total)
{
	const char	*base;
	int			error;

	base = "0123456789";
	if (n >= 10)
		total = ft_print_uint (n / 10, total);
	if (total < 0)
		return (-1);
	error = write (1, &base[n % 10], 1);
	if (error < 0)
		return (-1);
	return (total + 1);
}
