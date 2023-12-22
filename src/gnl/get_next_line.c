/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:11:14 by marvin            #+#    #+#             */
/*   Updated: 2023/10/16 11:51:46 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4096
#endif

int	newline_i(char *input, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if (input[i] == '\n')
			return (i);
	}
	return (-1);
}

t_buffers	*get_t_buffer(int fd, t_buffers **input)
{
	t_buffers	*new;
	t_buffers	*b;

	b = *input;
	while (b && b->fd != fd && b->next)
		b = b->next;
	if (b && b->fd == fd)
		return (b);
	new = (t_buffers *)malloc(sizeof(t_buffers));
	if (!new)
		return (0);
	*new = (t_buffers){.fd = fd, .index = BUFFER_SIZE, .end = BUFFER_SIZE,
		.buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE)};
	if (!new->buffer)
	{
		free(new);
		return (0);
	}
	if (b)
		b->next = new;
	else
		*input = new;
	return (new);
}

int	add_buff(t_buffers *b, int *lindex, int *len, char **line)
{
	*lindex = newline_i(b->buffer + b->index, b->end - b->index);
	*line = malloc(0);
	while (*lindex == -1 && b->end)
	{
		*len = reallojoin(line, *len, b->buffer + b->index, b->end - b->index);
		if (!*len)
		{
			free(*line);
			return (0);
		}
		b->end = read(b->fd, b->buffer, BUFFER_SIZE);
		if (b->end == -1)
		{
			free(*line);
			return (0);
		}
		b->index = 0;
		*lindex = newline_i(b->buffer, b->end);
	}
	return (1);
}

char	*get_next_line_main(t_buffers **file_buffer, t_buffers **b)
{
	int					lindex;
	char				*line;
	int					len;

	len = 0;
	if (((!(*b)->end || (*b)->end == -1) || !add_buff(*b, &lindex, &len, &line))
		&& remove_fd(file_buffer, (*b)->fd))
		return (0);
	if (!(*b)->end)
		return (line);
	if (!reallojoin(&line, len, (*b)->buffer + (*b)->index, lindex + 1)
		&& remove_fd(file_buffer, (*b)->fd))
	{
		free(line);
		return (0);
	}
	(*b)->index = (*b)->index + lindex + 1;
	return (line);
}

char	*get_next_line(int fd)
{
	static t_buffers	*file_buffer;
	t_buffers			*b;

	b = get_t_buffer(fd, &file_buffer);
	if (!b)
		return (0);
	if (b->index == b->end)
	{
		b->end = read(fd, b->buffer, BUFFER_SIZE);
		b->index = 0;
	}
	return (get_next_line_main(&file_buffer, &b));
}

// int main()
// {
// 	get_next_line(23);
// 	return (0);
// }
// int	main()
// {
// 	int file = open("get_next_line.c", O_RDONLY);
// 	int file2 = open("get_next_line.h", O_RDONLY);
// 	int file3 = open("tester3.txt", O_RDONLY);
// 	char *c = get_next_line(file2);
// //get_next_line(file2);

// 	printf("~~~~~~~~~~~~~~~\n");
// 	int i = 0;
// 	while (c )//|| d || e)
// 	{
// 		++i;
// 		get_next_line(file3);
// 			get_next_line(file);
// 			printf("%d: |%s|", i, c);
// 			c = get_next_line(file2);
// 			// printf("%d: %s", i, d);
// 		 	//get_next_line(file3);
// 			// printf("%d: %s", i, e);
// 	}
// 	printf("~~~~~~~~~~~~~~~\n");
// 	close(file);
// 	close(file2);
// 	close(file3);
// 	return (0);
// }
