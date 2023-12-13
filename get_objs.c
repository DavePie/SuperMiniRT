/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:11:59 by alde-oli          #+#    #+#             */
/*   Updated: 2023/12/13 13:11:59 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

char	*copy_word(char *line, int *i)
{
	int		j;
	char	*word;

	j = 0;
	while (line[*i + j] && line[*i + j] != ' ')
		j++;
	word = malloc(sizeof(char) * (j + 1));
	if (!word)
		return (NULL);
	j = 0;
	while (line[*i + j] && line[*i + j] != ' ')
	{
		word[j] = line[*i + j];
		j++;
	}
	word[j] = '\0';
	*i += j;
	return (word);
}

int	ft_custom_split(char *line, char ***split, int *atr)
{
	int i;
	int j;
	if (count_words(line) != (atr[0] + atr[1] + atr[2] + atr[3] + atr[4]))
		return (1);
	*split = malloc(sizeof(char *) * count_words(line));
	if (!*split)
		return (1);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			(*split)[j] = copy_word(line, &i);
			if (!(*split)[j])
			{
				ft_free_str_tab(*split);
				return (1);
			}
			j++;
		}
		else
			i++;
	}
	return (0);
}

unsigned int	get_color(char *line);
t_p	get_coords(char *line);
float	get_float(char *line);


int	match_type(char *line, int *i)
{
	static char *type[] = {"A", "C", "L", "sp", "pl", "cy"};


	*i = 0;
	while (line[*i] && type[*i])
	{
		if (ft_strncmp(line, type[*i], ft_strlen(type[*i])))
			return (*i);
		(*i)++;
	}
	return (-1);
}

//attr[i][] {color, coords1, coords2, dimension1, dimension2}
void	set_attributes(t_obj *new, char *line, int fd, t_scene *scene)
{
	int			i;
	char		**split;
	static int	a[6][5] = {{1, 0, 1, 1, 1}, {0, 1, 1, 1, 0},
							{1, 1, 0, 1, 0}, {1, 1, 0, 1, 0},
							{1, 1, 1, 0, 0}, {1, 1, 1, 1, 1}};
	if (match_type(line, &i) == -1 || ft_custom_split(line, &split, a[i]))
	{
		free(line);
		close(fd);
		ft_error(1, "Invalid scene element\n", 0, scene);
	}
	if (attr[i][0])
		new->color = get_color(split[a[i][0] + a[i][1] + a[i][2]]);
	if (attr[i][1])
		new->p = get_coords(split[1]);
	if (attr[i][2])
		new->v = get_coords(split[1]);
	if (attr[i][3])
		new->w = get_float(split[1]);
	if (attr[i][4])
		new->h = get_float(split[1]);
}

int	new_obj(t_scene *scene, int fd)
{
	t_obj	*new;
	char	*line;

	new = ft_malloc(sizeof(t_obj), scene);
	*new = (t_obj){};
	line = get_next_line(fd);
	if ((line[0] == 'A' && scene->ambient) || (line[0] == 'C' && scene->camera) ||
		(line[0] == 'L' && scene->lights))
	{
		free(line);
		ft_error(1, "Multiple definition of a scene element\n", 0, scene);
	}
	else if (line[0] == 'A')
		add_back(&scene->ambient, new);
	else if (line[0] == 'C')
		add_back(&scene->camera, new);
	else if (line[0] == 'L')
		add_back(&scene->lights, new);
	else
		add_back(&scene->objects, new);
	set_attributes(new, line, fd, scene);
}

void	get_objs(t_scene *scene, int fd)
{
	t_obj	*start;

	while (new_obj(scene, fd))
		continue ;
}
