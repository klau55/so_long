/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 20:40:19 by nkarpilo          #+#    #+#             */
/*   Updated: 2023/11/06 18:39:30 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	char	*ptr;
	int		length;

	length = 0;
	while (s[length])
		length++;
	dest = malloc(length + 1);
	if (dest == 0)
		return (0);
	ptr = dest;
	while (*s != '\0')
	{
		*dest = *s;
		dest++;
		s++;
	}
	*dest = '\0';
	return (ptr);
}
