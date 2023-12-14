/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:34:02 by dvandenb          #+#    #+#             */
/*   Updated: 2023/10/11 17:59:17 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*cur;
	t_list	*temp;

	if (!lst)
		return ;
	cur = *lst;
	while (cur)
	{
		temp = cur;
		cur = cur->next;
		del(temp->content);
		free(temp);
	}
	*lst = 0;
}
