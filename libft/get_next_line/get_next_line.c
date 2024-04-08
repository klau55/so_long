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

#include "../libft.h"

void	polish_text(t_glist **list)
{
	t_glist	*last_node;
	t_glist	*clean_node;
	int		i;
	int		k;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_glist));
	if (buf == NULL || clean_node == NULL)
		return ;
	last_node = find_last_node(*list);
	i = 0;
	k = 0;
	while (last_node->str_buf[i] != '\0'
		&& last_node->str_buf[i] != '\n')
		++i;
	while (last_node->str_buf[i] != '\0'
		&& last_node->str_buf[++i])
		buf[k++] = last_node->str_buf[i];
	buf[k] = '\0';
	clean_node->str_buf = buf;
	clean_node->next = NULL;
	dealloc(list, clean_node, buf);
}

int	found_newline(t_glist *list)
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

void	node_add(t_glist **list, char *buf)
{
	t_glist	*new_node;
	t_glist	*last_node;

	last_node = find_last_node(*list);
	new_node = malloc(sizeof(t_glist));
	if (new_node == NULL)
		return ;
	if (last_node == NULL)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->str_buf = buf;
	new_node->next = NULL;
}

void	create_list(t_glist **list, int fd)
{
	int		char_read;
	char	*buf;

	while (1 != found_newline(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return ;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (!char_read || char_read < 0)
		{
			free(buf);
			return ;
		}
		buf[char_read] = '\0';
		node_add(list, buf);
	}
}

char	*get_next_line(int fd)
{
	static t_glist	*list = NULL;
	char			*res;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &res, 0) < 0)
	{
		dealloc(&list, NULL, NULL);
		return (NULL);
	}
	create_list(&list, fd);
	if (list == NULL)
	{
		dealloc(&list, NULL, NULL);
		return (NULL);
	}
	res = line_get(list);
	polish_text(&list);
	return (res);
}

/*int	main(void)
{
	char	*res;
	int		fd;

	fd = open("ass.txt", O_RDONLY);
	res = get_next_line(fd);
	printf("%s", res);
	return (0);
}*/