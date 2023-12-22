/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:11:59 by alde-oli          #+#    #+#             */
/*   Updated: 2023/12/22 11:59:29 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "get_next_line.h"
#include "libft.h"
#include "get_objs.h"

//type[]{AMBIENT, CAMERA, LIGHT, SPHERE, PLANE, CYLINDER}
int	match_t(char *line, int *i, t_obj *new_obj)
{
	static char	*type[] = {"sp", "pl", "cy", "zz", "A", "C", "L"};

	printf("line: %s\n", line);
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
	if (count_words(line) != (atr[0] + atr[1] + atr[2] + atr[3] + atr[4] + 1))
		return (1);
	*split = ft_split(line, ' ');
	if (*split)
		return (0);
	return (1);
}

void	*float_ptr(char *str, t_scene *s)
{
	float		*ans;
	const float	a = ft_atof(str);

	ans = malloc(sizeof(float));
	ft_error(!ans, "Unable to allocate memory", 0, s);
	*ans = a;
	return (ans);
}

//attr[i][]                {coords1, coords2, float1, float2, color}
//	static int	a[6][5] = {{      0,       0,      1,      0,     1},  ambient
//						   {      1,       1,      1,      0,     0},  camera
//						   {      1,       0,      1,      0,     1},  light
//						   here bonus object
//						   {      1,       0,      1,      0,     1},  sphere
//						   {      1,       1,      0,      0,     1},  plane
//						   {      1,       1,      1,      1,     1}}; cylinder

typedef void	*(*t_g)(char *input, t_scene *scene);

void	set_attributes(t_obj *new_obj, char *line, int fd, t_scene *scene)
{
	int			t[3];
	char		**split;
	const int	a[7][5] = {{1, 0, 1, 0, 1}, {1, 1, 0, 0, 1}, {1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1}, {0, 0, 1, 0, 1}, {1, 1, 1, 0, 0}, {1, 0, 1, 0, 1}};
	const t_g	get_val[5] = {get_coords, get_coords, float_ptr, float_ptr,
		get_color};
	const void	*ptrs[5] = {&new_obj->p, &new_obj->v, &new_obj->w, &new_obj->h,
		&new_obj->color};

	split = NULL;
	if (match_t(line, &t[0], new_obj) == -1 || do_split(line, &split, a[t[0]]))
	{
		free(line);
		close(fd);
		ft_error(1, "Invalid scene element\n", 0, scene);
	}
	t[1] = -1;
	t[2] = 0;
	while (++(t[1]) < 5)
		if (a[t[0]][t[1]])
			*(void **)ptrs[t[1]] = get_val[t[1]](split[++(t[2])], scene);
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

// static void	print_scene(t_obj *obj)
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
}



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
