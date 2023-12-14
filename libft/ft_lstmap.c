/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:47:29 by dvandenb          #+#    #+#             */
/*   Updated: 2023/10/13 11:36:22 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*))
{
	t_list	*nlst;
	t_list	*cur;
	t_list	*prev;

	nlst = 0;
	cur = 0;
	prev = 0;
	while (lst)
	{
		prev = cur;
		cur = (t_list *)malloc(sizeof(*nlst));
		if (prev)
			prev->next = cur;
		if (!nlst)
			nlst = cur;
		if (!cur)
			ft_lstclear(&nlst, del);
		if (!cur)
			return (0);
		cur->content = f(lst->content);
		lst = lst->next;
	}
	if (cur)
		cur->next = 0;
	return (nlst);
}
