/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:53:13 by nkarpilo          #+#    #+#             */
/*   Updated: 2023/11/06 18:39:36 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		len1;
	int		len2;
	int		lentotal;

	if (!(s1) || !(s2))
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	lentotal = len1 + len2 + 1;
	res = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!(res))
		return (NULL);
	ft_strlcpy(res, s1, lentotal);
	ft_strlcat(res, s2, lentotal);
	return (res);
}
