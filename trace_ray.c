/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:44:04 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/15 14:13:33 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace_ray.h"
#include "minirt.h"

typedef void	(*t_INTER)(t_p, t_p, t_obj *, t_p *);

void	inter_ray_sphere(t_p p, t_p r, t_obj *sphere, t_p *ans)
{
	const t_p	n = (t_p){.x = p.x - sphere->p->x, .y = p.y - sphere->p->y,
		.z = p.z - sphere->p->z};
	const float	a = dot(r, r);
	const float	b = 2 * dot(n, r);
	const float	dis = (b * b) - (4 * a * (dot(n, n)) - (sphere->w * sphere->w));

	ans->z = FLT_MAX;
	if (dis < 0)
	{
		ans->x = FLT_MAX;
		ans->y = FLT_MAX;
		return ;
	}
	ans->x = (-b + sqrt(dis)) / (2 * a);
	ans->y = (-b - sqrt(dis)) / (2 * a);
}

t_obj	*calculate_ray(t_scene *s, t_p p, t_p r, t_p *range)
{
	float			min_l;
	t_obj			*min_o;
	t_obj			*cur;
	t_p				t;
	const t_INTER	intersect[2] = {&inter_ray_sphere};

	min_l = FLT_MAX;
	min_o = 0;
	cur = s->objects;
	while (cur)
	{
		intersect[cur->type](p, r, cur, &t);
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

// range->x : min, range->y: max
unsigned int	trace_ray(t_scene *s, t_p r, t_p range)
{
	float		min_l;
	const t_obj	*min_o = calculate_ray(s, *s->camera->p, r, &range);

	min_l = range.z;
	if (!min_o)
		return (0);
	return (lighting_sphere(s, *min_o, r, min_l));
}



void	loop_line(t_scene *s, float x)
{
	float		y;
	t_p			v;
	t_p			range;

	y = 0;
	range = (t_p){.x = 1, .y = FLT_MAX};
	while (++y < s->mlx->height && x != -1)
	{
		if (*s->multi_t->do_exit)
			pthread_exit(0);
		v = (t_p){.x = x / s->mlx->width - 0.5f, .y = y
			/ s->mlx->width - ((0.5f) * s->mlx->height
				/ s->mlx->width), .z = Z_OFFSET};
		norm(&v);
		put_pixel(s, x, y, trace_ray(s, v, range));
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

	s->multi_t = ft_malloc(sizeof(t_threads), s);
	s->multi_t->cur_x = ft_malloc(sizeof(int), s);
	s->multi_t->do_exit = ft_malloc(sizeof(int), s);
	*s->multi_t->cur_x = 0;
	*s->multi_t->do_exit = 0;
	s->multi_t->l = ft_malloc(sizeof(pthread_mutex_t), s);
	pthread_mutex_init(s->multi_t->l, NULL);
	i = -1;
	while (++i < NUM_THREADS)
		pthread_create(&(s->multi_t->pids[i]), NULL, &thread_rays, s);
}


