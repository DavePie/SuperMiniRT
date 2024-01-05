/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:11:59 by alde-oli          #+#    #+#             */
/*   Updated: 2024/01/05 14:20:19 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "get_next_line.h"
#include "libft.h"
#include "get_objs.h"

//type[]{AMBIENT, CAMERA, LIGHT, SPHERE, PLANE, CYLINDER}
int	match_t(char *line, int *i, t_obj *new_obj)
{
	static char	*type[] = {"sp", "pl", "cy", "co", "A", "C", "L"};

	while(line && *line == ' ')
		line++;
	*i = 0;
	while (line[*i] && type[*i])
	{
		if (*line == *type[*i] && line[ft_strlen(type[*i]) - 1]
			== type[*i][ft_strlen(type[*i]) - 1])
		{
			new_obj->type = malloc(sizeof(int));
			if (!new_obj->type)
				return (-1);
			*new_obj->type = *i;
			return (*i);
		}
		(*i)++;
	}
	return (-1);
}

int	do_split(char *line, char ***split, const int *atr)
{
	if (count_words(line) != (atr[0] + atr[1] + atr[2] + atr[3] + atr[4] + atr[5] + atr[6] + atr[7] + atr[8] + atr[9] + 1))
		return (1);
	*split = ft_split(line, ' ');
	if (*split)
		return (0);
	return (1);
}

void	*float_ptr(char *str, t_scene *scene, int *error)
{
	float		*ans;
	const float	a = ft_atof(str);

	(void)scene;
	if (!ft_is_number(str, 1) || a < 0)
	{
		*error = 1;
		return (NULL);
	}
	ans = malloc(sizeof(float));
	if (!ans)
	{
		*error = 1;
		return (NULL);
	}
	*ans = a;
	return (ans);
}

//attr[i][]                {coords1, coords2, float1, float2, color, spec, reflect, img, bump, dirsupt}
//	static int	a[6][5] = {{      0,       0,      1,      0,     1,    0,       0,   0,    0,       0},  ambient
//						   {      1,       1,      1,      0,     0,    0,       0,   0,    0,       0},  camera
//						   {      1,       0,      1,      0,     1,    0,       0,   0,    0,       0},  light
//						   here bonus object
//						   {      1,       0,      1,      0,     1,    0,       0,   0,    0,       0},  sphere
//						   {      1,       1,      0,      0,     1},  plane
//						   {      1,       1,      1,      1,     1}}; cylinder

typedef void	*(*t_g)(char *input, t_scene *scene, int *error);

void	set_attributes(t_obj *o, char *line, int fd, t_scene *scene)
{
	int			t[4];
	char		**split;
	const int	a[7][10] = {{1, 0, 1, 0, 1, 1, 1, 1, 1, 1},
	{1, 1, 0, 0, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
	{1, 1, 1, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 1, 0, 1, 0, 0, 0, 0, 0}};
	const t_g	get_val[10] = {get_coords, get_coords, float_ptr, float_ptr,
		get_color, float_ptr, float_ptr, get_img, get_img, int_ptr};
	const void	*ptrs[10] = {&o->p, &o->v, &o->w, &o->h, &o->color, &o->spec,
		&o->reflect, &o->i, &o->b, &o->dis};

	t[0] = 0;
	t[1] = -1;
	t[2] = 0;
	split = NULL;
	t[3] = (match_t(line, &t[0], o) == -1 || do_split(line, &split, a[t[0]]));
	while (++(t[1]) < 10 && !t[3])
		if (a[t[0]][t[1]])
			*(void **)ptrs[t[1]] = get_val[t[1]](split[++(t[2])], scene, &t[3]);
	if (o->v)
		o->v = norm(o->v);
	free(line);
	close(fd);
	split = ft_free_str_tab(split);
	ft_error(t[3], "Error while loading scene element\n", 0, scene);
}

int	get_one_obj(t_scene *scene, int fd, char *line, t_obj *new_obj)
{
	int		i;

	i = 0;
	while (line && line[i] == ' ')
		i++;
	if ((line[i] == 'A' && scene->ambient) || (line[i] == 'C' && scene->camera)
		|| (line[i] == 'L' && scene->lights))
	{
		free(line);
		ft_error(1, "Multiple definition of a scene element\n", 0, scene);
	}
	else if (line[i] == 'A')
		add_back(&scene->ambient, new_obj);
	else if (line[i] == 'C')
		add_back(&scene->camera, new_obj);
	else if (line[i] == 'L')
		add_back(&scene->lights, new_obj);
	else
		add_back(&scene->objects, new_obj);
	set_attributes(new_obj, line, fd, scene);
	printf("every attributes of object %d:\npos: %p\nvector: %p\nwidth: %p\nheight: %p\ncolor: %p\nspec: %p\nreflect: %p\nimg: %p\nbump: %p\ndisruption: %p\n",
			*new_obj->type, new_obj->p, new_obj->v, new_obj->w, new_obj->h, new_obj->color, new_obj->spec, new_obj->reflect, new_obj->i, new_obj->b, new_obj->dis);
	return (1);
}

void	get_objs(t_scene *scene, int fd)
{
	t_obj	*new_obj;
	char	*line;

	while (1)
	{
		new_obj = ft_malloc(sizeof(t_obj), scene);
		*new_obj = (t_obj){};
		line = get_next_line(fd);
		if (!line || *line == '\0')
		{
			if (line)
				free(line);
			break ;
		}
		if (*line == '\n')
			free(line);
		else
			get_one_obj(scene, fd, line, new_obj);
	}
	if (!scene->camera || !scene->ambient || !scene->lights)
		ft_error(1, "Missing scene element\n", 0, scene);
}
