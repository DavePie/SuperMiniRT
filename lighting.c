/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:35:08 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/18 13:36:17 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lighting.h"

float	diffuse_light(t_scene *s, t_p p, t_p n)
{
	float		i;
	t_obj		*l;
	t_p			l_v;
	float		dot_l;
	t_p			range;

	range = (t_p){.x = 0.01, .y = FLT_MAX};
	i = s->ambient->w;
	l = s->lights;
	while (l)
	{
		l_v = (t_p){.x = l->p->x - p.x, .y = l->p->y - p.y, .z = l->p->z - p.z};
		norm(&l_v);
		if (calculate_ray(s, p, l_v, &range))
		{
			l = l->next;
			continue ;
		}
		dot_l = dot(n, l_v);
		if (dot_l > 0)
			i += l->w * dot_l / (mag(n) * mag(l_v));
		l = l->next;
	}
	return (i);
}

float	lighting_sphere(t_scene *s, t_obj o, t_p d, float m)
{
	const t_p	c = *s->camera->p;
	const t_p	p = (t_p){.x = c.x + (m * d.x), .y = c.y + (m * d.y),
		.z = c.z + (m * d.z)};
	t_p			n;

	n = (t_p){.x = p.x - o.p->x, .y = p.y - o.p->y, .z = p.z - o.p->z};
	norm(&n);
	return (color_mult(o.color, diffuse_light(s, p, n)));
}

static t_p	calculate_cylinder_normal(t_obj o, t_p p)
{
	const t_p	cp = {p.x - o.p->x, p.y - o.p->y, p.z - o.p->z};
	const float	proj_l = dot(cp, *o.v);
	const float	ep = 0.001;
	t_p			proj;
	t_p			normal;

	if (fabs(proj_l) < ep)
		return ((t_p){-o.v->x, -o.v->y, -o.v->z});
	else if (fabs(proj_l - o.h) < ep)
		return ((t_p){o.v->x, o.v->y, o.v->z});
	else
	{
		proj = (t_p){proj_l * o.v->x,
			proj_l * o.v->y, proj_l * o.v->z};
		normal = (t_p){cp.x - proj.x, cp.y - proj.y, cp.z - proj.z};
		norm(&normal);
		return (normal);
	}
}

float	lighting_cylinder(t_scene *s, t_obj o, t_p d, float m)
{
	const t_p	c = *s->camera->p;
	const t_p	p = (t_p){.x = c.x + (m * d.x), .y = c.y + (m * d.y),
		.z = c.z + (m * d.z)};
	t_p			n;

	n = calculate_cylinder_normal(o, p);
	norm(&n);
	return (color_mult(o.color, diffuse_light(s, p, n)));
}

float	lighting_plane(t_scene *s, t_obj o, t_p d, float m)
{
	const t_p	c = *s->camera->p;
	const t_p	p = (t_p){.x = c.x + (m * d.x), .y = c.y + (m * d.y),
		.z = c.z + (m * d.z)};

	return (color_mult(o.color, diffuse_light(s, p, *o.v)));
}
