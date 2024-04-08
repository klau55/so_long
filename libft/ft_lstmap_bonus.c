/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarpilo <nkarpilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:05:23 by nkarpilo          #+#    #+#             */
/*   Updated: 2023/11/09 16:48:31 by nkarpilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	t_list	*res;
	t_list	*curr_content;

	start = NULL;
	while (lst)
	{
		curr_content = f(lst->content);
		res = ft_lstnew(curr_content);
		if (!res)
		{
			ft_lstclear(&res, del);
			free(curr_content);
		}
		ft_lstadd_back(&start, res);
		lst = lst->next;
	}
	return (start);
}
