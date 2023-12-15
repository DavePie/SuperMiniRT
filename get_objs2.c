/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objs2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:05:22 by alde-oli          #+#    #+#             */
/*   Updated: 2023/12/14 18:09:22 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "get_next_line.h"
#include "libft.h"
#include "get_objs.h"

int	count_words(char *str)
{
	int	prev_char;
	int	cur_char;
	int	total;

	total = 0;
	prev_char = 1;
	while (*str)
	{
		cur_char = *str++ == ' ';
		if (!cur_char && prev_char)
			total++;
		prev_char = cur_char;
	}
	return (total);
}

unsigned int	get_color(char *line)
{
	char			**split;
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;

	split = ft_split(line, ',');
	green = ft_atoi(split[0]);
	blue = ft_atoi(split[1]);
	red = ft_atoi(split[2]);
	free(split);
	return (cl(red, green, blue));
}

t_p	*get_coords(char *line, t_scene *s)
{
	char	**split;
	t_p		*coords;

	split = ft_split(line, ',');
	ft_error(!split, "malloc error", 0, s);
	coords = (t_p *) malloc(sizeof(t_p) * 1);
	if (!coords)
	{
		ft_free_str_tab(split);
		ft_error(1, "malloc error", 0, s);
	}
	coords->x = ft_atof(split[0]);
	coords->y = ft_atof(split[1]);
	coords->z = ft_atof(split[2]);
	free(split);
	return (coords);
}
