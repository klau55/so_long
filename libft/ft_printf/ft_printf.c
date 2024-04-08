/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:37:30 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/04/05 20:26:00 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_set_format(va_list args, const char format)
{
	if (format == 'c')
		return (ft_print_char(va_arg(args, int)));
	else if (format == 'd' || format == 'i')
		return (ft_print_num(va_arg(args, int), 0));
	else if (format == 's')
		return (ft_print_str(va_arg(args, char *), 0));
	else if (format == '%')
		return (ft_print_char('%'));
	else if (format == 'x' || format == 'X')
		return (ft_print_hex(va_arg(args, unsigned int), format, 0));
	else if (format == 'p')
		return (ft_print_ptr(va_arg(args, void *), 0));
	else if (format == 'u')
		return (ft_print_uint(va_arg(args, unsigned int), 0));
	return (-1);
}

int	ft_processor(va_list args, const char *format)
{
	int	i;
	int	total;
	int	temp;

	i = -1;
	total = 0;
	temp = 0;
	while (format[++i])
	{
		if (format[i] == '%')
		{
			temp = ft_set_format(args, format[++i]);
			if (temp < 0)
				return (-1);
			total += temp;
		}
		else if (ft_print_char(format[i]) >= 0)
			++total;
		else
			return (-1);
	}
	return (total);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		total;

	va_start(args, format);
	total = ft_processor(args, format);
	va_end(args);
	if (total < 0)
		return (-1);
	return (total);
}
