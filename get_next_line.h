/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:48:37 by nkarpilo          #+#    #+#             */
/*   Updated: 2023/11/28 17:20:01 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	char			*str_buf;
	struct s_list	*next;
}	t_list;

void	dealloc(t_list **list, t_list *clean_node, char *buf);
t_list	*find_last_node(t_list *list);
int		polish_text(t_list **list);
int		len_to_newline(t_list *list);
void	copy_str(t_list *list, char *str);
char	*line_get(t_list *list);
int		found_newline(t_list *list);
int		node_add(t_list **list, char *buf);
int		create_list(t_list **list, int fd);
char	*get_next_line(int fd);

#endif