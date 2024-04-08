/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:16:03 by nkarpilo          #+#    #+#             */
/*   Updated: 2024/04/05 20:05:38 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

void	dealloc(t_glist **list, t_glist *clean_node, char *buf)
{
	t_glist	*tmp;

	if (*list == NULL)
		return ; 
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->str_buf);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (clean_node && clean_node->str_buf[0])
		*list = clean_node;
	else if (buf && clean_node)
	{
		free(buf);
		free(clean_node);
	}
}

t_glist	*find_last_node(t_glist *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

int	len_to_newline(t_glist *list)
{
	int		i;
	int		len;

	if (list == NULL)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->str_buf[i])
		{
			if (list->str_buf[i] == '\n')
				return (++len);
			++i;
			++len;
		}
		list = list->next;
	}
	return (len);
}

void	copy_str(t_glist *list, char *str)
{
	int		i;
	int		k;

	if (list == NULL)
		return ;
	k = 0;
	while (list)
	{
		i = 0;
		while (list->str_buf[i])
		{
			if (list->str_buf[i] == '\n')
			{
				str[k] = '\n';
				str[++k] = '\0';
				return ;
			}
			str[k++] = list->str_buf[i++];
		}
		list = list->next;
	}
	str[k] = '\0';
	return ;
}

char	*line_get(t_glist *list)
{
	int		str_len;
	char	*next_str;

	if (list == NULL)
		return (NULL);
	str_len = len_to_newline(list);
	next_str = malloc(str_len + 1);
	if (next_str == NULL)
		return (NULL);
	copy_str(list, next_str);
	return (next_str);
}
