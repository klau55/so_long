/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 20:08:51 by nkarpilo          #+#    #+#             */
/*   Updated: 2023/11/13 14:27:15 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	memmove_forward(char *cdest, char *csrc, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		cdest[i] = csrc[i];
		i++;
	}
}

static void	memmove_backward(char *cdest, char *csrc, size_t n)
{
	size_t	i;

	i = n;
	while (i > 0)
	{
		cdest[i - 1] = csrc[i - 1];
		i--;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*csrc;
	char	*cdest;

	csrc = (char *)src;
	cdest = (char *)dest;
	if (!dest && !src)
		return (NULL);
	if (cdest < csrc)
		memmove_forward(cdest, csrc, n);
	else if (cdest > csrc)
		memmove_backward(cdest, csrc, n);
	return (dest);
}
