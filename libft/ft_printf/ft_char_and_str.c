/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_and_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:08:53 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/04/05 20:25:40 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_print_char(int c)
{
	return (write(1, &c, 1));
}

int	ft_print_str(char *s, int total)
{
	if (s == NULL)
	{
		if (ft_print_str("(null)", total) < 0)
			return (-1);
		return (6);
	}
	while (*s)
	{
		if (ft_print_char(*s++) < 0)
			return (-1);
		total++;
	}
	return (total);
}
