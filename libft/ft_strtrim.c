/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:17:50 by nkarpilo          #+#    #+#             */
/*   Updated: 2023/11/13 14:27:19 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_trim_start(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while (s1[i] != set[j])
		{
			if (set[j] == '\0')
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

static int	ft_trim_end(char const *s1, char const *set)
{
	int	i;
	int	j;

	j = 0;
	i = ft_strlen(s1) - 1;
	while (i >= 0)
	{
		j = 0;
		while (s1[i] != set[j])
		{
			if (!set[j])
				return (i);
			j++;
		}
		i--;
	}
	return (-1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*s_new;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	if (ft_trim_start(s1, set) < 0)
		return (ft_strdup(""));
	start = ft_trim_start(s1, set);
	end = ft_trim_end(s1, set);
	s_new = (char *) malloc(sizeof(char) * (end - start + 2));
	if (!s_new)
		return (s_new);
	i = end - start;
	while (i >= 0)
	{
		s_new[i] = s1[start + i];
		i--;
	}
	s_new[end - start + 1] = '\0';
	return (s_new);
}
