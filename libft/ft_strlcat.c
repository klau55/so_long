/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 20:31:36 by nkarpilo          #+#    #+#             */
/*   Updated: 2023/11/06 18:39:48 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	space_left;
	size_t	copy_len;
	size_t	i;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (dest_len >= destsize)
		return (destsize + src_len);
	space_left = destsize - dest_len - 1;
	copy_len = src_len;
	if (src_len > space_left)
		copy_len = space_left;
	i = 0;
	while (i < copy_len)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + copy_len] = '\0';
	return (dest_len + src_len);
}
