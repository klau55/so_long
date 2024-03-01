/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:48:33 by nkarpilo          #+#    #+#             */
/*   Updated: 2023/11/28 17:19:54 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	polish_text(t_list **list)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		k;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (-1);
	clean_node = malloc(sizeof(t_list));
	if (clean_node == NULL)
		return (free(buf), -1);
	last_node = find_last_node(*list);
	i = 0;
	k = 0;
	while (last_node->str_buf[i] != '\0'
		&& last_node->str_buf[i] != '\n')
		++i;
	while (last_node->str_buf[i] != '\0' && last_node->str_buf[++i])
		buf[k++] = last_node->str_buf[i];
	buf[k] = '\0';
	clean_node->str_buf = buf;
	clean_node->next = NULL;
	dealloc(list, clean_node, buf);
	return (0);
}

int	found_newline(t_list *list)
{
	int	i;

	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->str_buf[i] != '\n' && list->str_buf[i] != '\0')
			i++;
		if (list->str_buf[i] == '\n')
			return (1);
		else
			list = list->next;
	}
	return (0);
}

int	node_add(t_list **list, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = find_last_node(*list);
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return (-1);
	if (last_node == NULL)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->str_buf = buf;
	new_node->next = NULL;
	return (0);
}

int	create_list(t_list **list, int fd)
{
	int		char_read;
	char	*buf;

	while (1 != found_newline(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return (-1);
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read < 0)
			return (free(buf), -1);
		else if (char_read == 0)
			return (free(buf), 0);
		buf[char_read] = '\0';
		if (-1 == node_add(list, buf))
			return (free(buf), -1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*res;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &res, 0) < 0)
		return (dealloc(&list, NULL, NULL), NULL);
	if (-1 == create_list(&list, fd) || !list)
		return (dealloc(&list, NULL, NULL), NULL);
	res = line_get(list);
	if (!res)
		return (dealloc(&list, 0, 0), NULL);
	if (-1 == polish_text(&list))
		return (free(res), dealloc(&list, 0, 0), NULL);
	return (res);
}
