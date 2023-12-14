/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objs2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:05:22 by alde-oli          #+#    #+#             */
/*   Updated: 2023/12/14 16:15:28 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "get_next_line.h"
#include "libft.h"
#include "get_objs.h"

int	count_words(char *line)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			words++;
			while (line[i] && line[i] != ' ')
				i++;
		}
		else
			i++;
	}
	return (words);
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

t_p	*get_coords(char *line)
{
	char	**split;
	t_p		*coords;

	split = ft_split(line, ',');
	coords = (t_p *) malloc(sizeof(t_p) * 1);
	coords->x = ft_atof(split[0]);
	coords->y = ft_atof(split[1]);
	free(split);
	return (coords);
}
