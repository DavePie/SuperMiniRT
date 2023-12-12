/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:51:04 by dvandenb          #+#    #+#             */
/*   Updated: 2023/10/16 11:51:52 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	reallojoin(char **dest, int cur_size, char *src, int src_size)
{
	char	*temp;
	int		i;

	i = -1;
	temp = (char *)malloc(sizeof(char) * (cur_size + src_size + 1));
	if (!temp)
		return (0);
	while (++i < cur_size)
		temp[i] = (*dest)[i];
	while (i < cur_size + src_size)
	{
		temp[i] = src[i - cur_size];
		i++;
	}
	temp[i] = '\0';
	free(*dest);
	*dest = temp;
	return (cur_size + src_size);
}

int	remove_fd(t_buffers **begin_list, int fd)
{
	t_buffers	*prev;
	t_buffers	*cur;
	t_buffers	*temp;

	cur = *begin_list;
	prev = 0;
	while (cur)
	{
		if (cur->fd == fd)
		{
			if (prev)
				prev->next = prev->next->next;
			else
				*begin_list = (*begin_list)->next;
			temp = cur;
			cur = cur->next;
			free(temp->buffer);
			free(temp);
			continue ;
		}
		prev = cur;
		cur = cur->next;
	}
	return (1);
}
