/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:13:45 by marvin            #+#    #+#             */
/*   Updated: 2023/10/18 16:25:46 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_buffers
{
	int					fd;
	char				*buffer;
	struct s_buffers	*next;
	int					index;
	int					end;
}	t_buffers;
char	*get_next_line(int fd);
int		reallojoin(char **dest, int cur_size, char *src, int src_size);
int		remove_fd(t_buffers **begin_list, int fd);
#endif