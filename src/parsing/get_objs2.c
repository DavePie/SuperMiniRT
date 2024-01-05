/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objs2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:05:22 by alde-oli          #+#    #+#             */
/*   Updated: 2024/01/05 14:18:54 by alde-oli         ###   ########.fr       */
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

void	*get_color(char *line, t_scene *scene , int *error)
{
	char	**split;
	int		color[3];
	int		i;
	t_p		*ans;

	(void)scene;
	split = ft_split(line, ',');
	if (!split && printf("error while getting color: value set to 0\n"))
		*error = 1;
	i = -1;
	while (!*error && ++i < 3)
	{
		color[i] = ft_atoi(split[i]);
		if (!ft_is_number(split[i], 0) || color[i] < 0 || color[i] > 255)
			*error = 1;
	}
	if (split)
		ft_free_str_tab(split);
	ans = malloc(sizeof(t_p));
	if (!ans)
		*error = 1;
	if (ans && !*error)
		*ans = (t_p){.x = color[0], .y = color[1], .z = color[2]};
	return (ans);
}

void	*get_coords(char *line, t_scene *scene, int *error)
{
	char	**split;
	t_p		*coords;

	(void)scene;
	split = ft_split(line, ',');
	if (split)
		coords = (t_p *) malloc(sizeof(t_p) * 1);
	if (!split || !coords)
	{
		ft_free_str_tab(split);
		*error = 1;
		return (NULL);
	}
	coords->x = ft_atof(split[0]);
	coords->y = ft_atof(split[1]);
	coords->z = ft_atof(split[2]);
	free(split);
	return (coords);
}

void	*get_img(char *line, t_scene *scene, int *error)
{
	t_img		*img;
	const int	len = ft_strlen(line);
	int			i;

	if (line[0] == '0' && ft_strlen(line) == 1)
		return (NULL);
	img = malloc(sizeof(t_img));
	if (!img || len < 5 || ft_strncmp(line + len - 4, ".xpm", 4))
	{
		*error = 1;
		return (NULL);
	}
	i = 0;
	if (!*error)
		img->img = mlx_xpm_file_to_image(scene->mlx->mlx,
				line, &img->w, &img->h);
	if (img->img)
		img->pix = mlx_get_data_addr(img->img, &i, &i, &i);
	if (!img->img || !img->pix)
	{
		*error = 1;
		return (NULL);
	}
	return (img);
}

void	*int_ptr(char *str, t_scene *scene, int *error)
{
	int	*ans;

	(void)scene;
	ans = malloc(sizeof(int));
	if (!ans || !ft_is_number(str, 0) || ft_strlen(str) > 2
		|| ft_atoi(str) < 0)
	{
		*error = 1;
		return (NULL);
	}
	*ans = ft_atoi(str);
	printf("ans = %d\n", *ans);
	return (ans);
}
