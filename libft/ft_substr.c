/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:53:56 by nkarpilo          #+#    #+#             */
/*   Updated: 2023/11/13 14:27:21 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	substr_loop(char *s, char *res, size_t len, unsigned int i)
{
	unsigned int	j;

	j = 0;
	{
		while (s != '\0' && len > 0)
		{
			res[j] = s[i];
			j++;
			len--;
			i++;
		}
	}
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	s_len;
	unsigned int	i;
	char			*res;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len - start < len)
		len = s_len - start;
	if (s_len <= start)
		return (ft_strdup(""));
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i <= s_len)
	{
		if (i == start && len > 0)
			substr_loop((char *)s, res, len, i);
		i++;
	}
	res[len] = '\0';
	return (res);
}
