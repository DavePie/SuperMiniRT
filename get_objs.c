/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:11:59 by alde-oli          #+#    #+#             */
/*   Updated: 2023/12/14 15:08:48 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "get_next_line.h"
#include "libft.h"
#include "get_objs.h"

//type[]{AMBIENT, CAMERA, LIGHT, SPHERE, PLANE, CYLINDER}
int	match_type(char *line, int *i, t_obj *new_obj)
{
	static char	*type[] = {"A", "C", "L", "sp", "pl", "cy"};

	*i = 0;
	while (line[*i] && type[*i])
	{
		if (!ft_strncmp(line, type[*i], ft_strlen(type[*i])))
		{
			new_obj->type = *i;
			return (*i);
		}
		(*i)++;
	}
	return (-1);
}

int	do_split(char *line, char ***split, int *atr)
{
	if (count_words(line) != (atr[0] + atr[1] + atr[2] + atr[3] + atr[4] + 1))
		return (1);
	*split = ft_split(line, ' ');
	if (*split)
		return (0);
	return (1);
}

//attr[i][]                {coords1, coords2, float1, float2, color}
//	static int	a[6][5] = {{      0,       0,      1,      0,     1},  ambient
//						   {      1,       1,      1,      0,     0},  camera
//						   {      1,       0,      1,      0,     1},  light
//						   {      1,       0,      1,      0,     1},  sphere
//						   {      1,       1,      0,      0,     1},  plane
//						   {      1,       1,      1,      1,     1}}; cylinder
void	set_attributes(t_obj *new_obj, char *line, int fd, t_scene *scene)
{
	int			i;
	char		**split;
	static int	a[6][5] = {{0, 0, 1, 0, 1}, {1, 1, 1, 0, 0}, {1, 0, 1, 0, 1},
	{1, 0, 1, 0, 1}, {1, 1, 0, 0, 1}, {1, 1, 1, 1, 1}};

	split = NULL;
	if (match_type(line, &i, new_obj) == -1 || do_split(line, &split, a[i]))
	{
		free(line);
		close(fd);
		ft_error(1, "Invalid scene element\n", 0, scene);
	}
	if (a[i][0])
		new_obj->p = get_coords(split[a[i][0]]);
	if (a[i][1])
		new_obj->v = get_coords(split[a[i][0] + a[i][1]]);
	if (a[i][2])
		new_obj->w = ft_atof(split[a[i][0] + a[i][1] + a[i][2]]);
	if (a[i][3])
		new_obj->h = ft_atof(split[a[i][0] + a[i][1] + a[i][2] + a[i][3]]);
	if (a[i][4])
		new_obj->color = get_color(split[a[i][0] + a[i][1] + a[i][2]
				+ a[i][3] + a[i][4]]);
	free(line);
	ft_free_str_tab(split);
}

int	get_one_obj(t_scene *scene, int fd, char *line, t_obj *new_obj)
{
	if ((line[0] == 'A' && scene->ambient) || (line[0] == 'C' && scene->camera)
		|| (line[0] == 'L' && scene->lights))
	{
		free(line);
		ft_error(1, "Multiple definition of a scene element\n", 0, scene);
	}
	else if (line[0] == 'A')
		add_back(&scene->ambient, new_obj);
	else if (line[0] == 'C')
		add_back(&scene->camera, new_obj);
	else if (line[0] == 'L')
		add_back(&scene->lights, new_obj);
	else
		add_back(&scene->objects, new_obj);
	set_attributes(new_obj, line, fd, scene);
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
			return ;
		}
		if (*line == '\n')
			free(line);
		else
			get_one_obj(scene, fd, line, new_obj);
	}
}

// void	print_scene(t_obj *obj)
// {
// 	if (obj->type == AMBIENT)
// 		printf("Ambient\n");
// 	else if (obj->type == CAMERA)
// 		printf("Camera\n");
// 	else if (obj->type == LIGHT)
// 		printf("Light\n");
// 	else if (obj->type == SPHERE)
// 		printf("Sphere\n");
// 	else if (obj->type == PLANE)
// 		printf("Plane\n");
// 	else if (obj->type == CYLINDER)
// 		printf("Cylinder\n");
// 	else
// 		printf("Unknown type\n");
// 	printf("type: %d\n", obj->type);
// 	if (obj->p)
// 		printf("pos: %f, %f, %f\n", obj->p->x, obj->p->y,
// 			obj->p->z);
// 	if (obj->v)
// 		printf("v: %f, %f, %f\n", obj->v->x, obj->v->y,
// 			obj->v->z);
// 	printf("w: %f\n", obj->w);
// 	printf("h: %f\n", obj->h);
// 	printf("color: r = %d, g = %d, b = %d\n", (obj->color >> 16) & 0xFF,
// 		(obj->color >> 8) & 0xFF, obj->color & 0xFF);
// 	printf("\n\n");
// }

// void	get_objs(t_scene *scene, int fd)
// {
// 	while (get_one_obj(scene, fd))
// 		continue ;
// 	printf("ambient type is %d\n", scene->ambient->type);
// 	print_scene(scene->ambient);
// 	print_scene(scene->camera);
// 	print_scene(scene->lights);
// 	t_obj *obj = scene->objects;
// 	while (obj)
// 	{
// 		print_scene(obj);
// 		obj = obj->next;
// 	}
// }
