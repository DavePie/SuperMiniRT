/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:44:04 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/13 17:19:26 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace_ray.h"
#include "minirt.h"

typedef void	(*t_INTER)(t_scene *, t_p, t_obj *, t_p *);

void	inter_ray_sphere(t_scene *s, t_p r, t_obj *sphere, t_p *ans)
{
	const t_p	c = *s->camera->p;
	const t_p	v = (t_p){.x = c.x - sphere->p->x, .y = c.y - sphere->p->y,
		.z = c.z - sphere->p->z};
	const float	a = dot(r, r);
	const float	b = 2 * dot(v, r);
	const float	dis = (b * b) - (4 * a * (dot(v, v)) - (sphere->w * sphere->w));

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

unsigned int	trace_ray(t_scene *s, t_p r, float min, float max)
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
		intersect[cur->type](s, r, cur, &t);
		if ((t.x >= min && t.x < max && t.x <= min_l)
			|| (t.y >= min && t.y < max && t.y <= min_l))
			min_o = cur;
		if ((t.x >= min && t.x < max && t.x <= min_l))
			min_l = t.x;
		if (t.y >= min && t.y < max && t.y <= min_l)
			min_l = t.y;
		cur = cur->next;
	}
	if (!min_o)
		return (255);
	return (min_o->color);
}

void	trace_rays(t_scene *s)
{
	float	x;
	float	y;
	t_p		v;

	x = 0;
	while (++x < s->mlx->width)
	{
		y = 0;
		while (++y < s->mlx->height)
		{
			v = (t_p){.x = x / s->mlx->width, .y = y / s->mlx->width, .z = 1};
			put_pixel(s, x, y, trace_ray(s, v, 1, FLT_MAX));
		}
	}
}
