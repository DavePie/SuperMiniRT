/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:44:04 by dvandenb          #+#    #+#             */
/*   Updated: 2024/01/09 08:56:37 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace_ray.h"
#include "minirt.h"

typedef void	(*t_INTER)(t_p, t_p, t_obj *, t_p *);
typedef float	(*t_LIGHT)(t_scene *, t_obj, t_p, int);

t_obj	*calculate_ray(t_scene *s, t_p p, t_p r, t_p *range)
{
	float			min_l;
	t_obj			*min_o;
	t_obj			*cur;
	t_p				t;
	const t_INTER	intersect[4] = {&inter_ray_sphere, &inter_ray_plane,
		&inter_ray_cylinder, &inter_ray_cone};

	min_l = FLT_MAX;
	min_o = 0;
	cur = s->objects;
	while (cur)
	{
		intersect[*(cur->type)](p, r, cur, &t);
		if ((t.x >= range->x && t.x <= range->y && t.x < min_l)
			|| (t.y >= range->x && t.y <= range->y && t.y < min_l))
			min_o = cur;
		if ((t.x >= range->x && t.x <= range->y && t.x < min_l))
			min_l = t.x;
		if (t.y >= range->x && t.y <= range->y && t.y < min_l)
			min_l = t.y;
		cur = cur->next;
	}
	range->z = min_l;
	return (min_o);
}

t_p	trace_ray(t_scene *s, t_p input[2], t_p range, int depth)
{
	float			min_l;
	const t_obj		*min_o = calculate_ray(s, input[0], input[1], &range);

	min_l = range.z;
	mult(input[1], min_l, &input[1]);
	if (!min_o)
		return ((t_p){0, 0, 0});
	return (lighting(s, *min_o, input, depth));
}

void	loop_line(t_scene *s, float x_w)
{
	float		y_w;
	t_p			input[2];
	t_p			range;
	float		x;
	float		y;

	y_w = 0;
	range = (t_p){.x = 1, .y = FLT_MAX};
	input[0] = *s->camera->p;
	while (++y_w < s->mlx->height && x_w != -1)
	{
		if (s->multi_t->do_exit)
			pthread_exit(0);
		x = x_w / s->mlx->width - 0.5f;
		y = y_w / s->mlx->width - ((0.5f) * s->mlx->height / s->mlx->width);
		input[1] = (t_p){.x = s->camera->v->x + (x * s->o_x.x) + (y * s->o_y.x),
			.y = s->camera->v->y + (x * s->o_x.y) + (y * s->o_y.y),
			.z = s->camera->v->z + (x * s->o_x.z) + (y * s->o_y.z)};
		norm(&input[1]);
		put_pixel(s, x_w, y_w, trace_ray(s, input, range, 100));
	}
}

void	*thread_rays(void *ss)
{
	float		x;
	t_scene		*s;

	s = (t_scene *)ss;
	x = -1;
	while (x < s->mlx->width)
	{
		loop_line(s, x);
		pthread_mutex_lock(s->multi_t->l);
		x = *s->multi_t->cur_x;
		(*s->multi_t->cur_x)++;
		pthread_mutex_unlock(s->multi_t->l);
	}
	return (0);
}

void	trace_rays(t_scene *s)
{
	int			i;
	const t_p	c = *s->camera->v;

	s->multi_t = ft_malloc(sizeof(t_threads), s);
	s->multi_t->cur_x = ft_malloc(sizeof(int), s);
	*s->multi_t->cur_x = 0;
	s->multi_t->do_exit = 0;
	s->multi_t->l = ft_malloc(sizeof(pthread_mutex_t), s);
	pthread_mutex_init(s->multi_t->l, NULL);
	i = -1;
	s->o_x = (t_p){.x = c.z, .y = 0, .z = -c.x};
	norm(&s->o_x);
	cross(c, s->o_x, &s->o_y);
	norm(&s->o_y);
	while (++i < NUM_THREADS)
		pthread_create(&(s->multi_t->pids[i]), NULL, &thread_rays, s);
}
