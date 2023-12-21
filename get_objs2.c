/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objs2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:05:22 by alde-oli          #+#    #+#             */
/*   Updated: 2023/12/21 17:51:04 by dvandenb         ###   ########.fr       */
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

unsigned int	*get_color(char *line)
{
	char			**split;
	int				color[3];
	int				i;
	unsigned int	*ans;

	split = ft_split(line, ',');
	if (!split && printf("error while getting color: value set to 0\n"))
		return (0);
	i = -1;
	while (++i < 3)
	{
		color[i] = ft_atoi(split[i]);
		if (!ft_is_number(split[i], 0) || color[i] < 0 || color[i] > 255)
		{
			printf("comp %c of color invalid or not 0-255 range: set to 255\n",
				('r' * i == 0) + ('g' * i == 1) + ('b' * i == 2));
			color[i] = 255;
		}
	}
	ft_free_str_tab(split);
	ans = malloc(sizeof(unsigned int));
	if (!ans)
		return (0);
	*ans = cl(color[0], color[1], color[2]);
	return (ans);
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
