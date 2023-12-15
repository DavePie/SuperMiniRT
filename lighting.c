/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:35:08 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/15 14:29:20 by dvandenb         ###   ########.fr       */
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
