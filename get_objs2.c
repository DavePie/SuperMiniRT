/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objs2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:05:22 by alde-oli          #+#    #+#             */
/*   Updated: 2023/12/21 11:53:19 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "get_next_line.h"
#include "libft.h"
#include "get_objs.h"

int	count_words(char *str)
{
	int	words;

	words = 0;
	while (*str && *str != '\n')
	{
		if (*str == ' ')
			while (*str == ' ')
				str++;
		else
		{
			words++;
			while (*str && *str != ' ')
				str++;
		}
	}
	return (words);
}

unsigned int	get_color(char *line)
{
	char			**split;
	int				color[3];
	int				i;

	split = ft_split(line, ',');
	if (!split)
	{
		printf("error while getting color: value set to 0\n");
		return (0);
	}
	i = 0;
	while (i < 3)
	{
		color[i] = ft_atoi(split[i]);
		if (!ft_is_number(split[i], 0) || color[i] < 0 || color[i] > 255)
		{
			printf("comp %c of color invalid or out of 0-255 range",
				('r' * i == 0) + ('g' * i == 1) + ('b' * i == 2));
			printf(": value set to 255\n");
			color[i] = 255;
		}
		i++;
	}
	ft_free_str_tab(split);
	return (cl(color[0], color[1], color[2]));
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
