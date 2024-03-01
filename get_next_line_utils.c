/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:16:03 by nkarpilo          #+#    #+#             */
/*   Updated: 2023/12/13 15:28:09 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	dealloc(t_list **list, t_list *clean_node, char *buf)
{
	t_list	*tmp;

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
	if (clean_node == 0 || buf == 0)
		return ;
	if (clean_node && clean_node->str_buf[0])
		*list = clean_node;
	else if (buf && clean_node)
	{
		free(buf);
		free(clean_node);
	}
}

t_list	*find_last_node(t_list *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

int	len_to_newline(t_list *list)
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

void	copy_str(t_list *list, char *str)
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

char	*line_get(t_list *list)
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
