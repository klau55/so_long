/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:08:53 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/04/05 20:26:02 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_print_ptr(void *ptr, int total)
{
	int	add;

	add = write (1, "0x", 2);
	if (add < 0)
		return (-1);
	total = (add + ft_print_hex((unsigned long)ptr, 0, total));
	if (total < 0)
		return (-1);
	return (total);
}
