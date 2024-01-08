/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:35:08 by dvandenb          #+#    #+#             */
/*   Updated: 2024/01/08 18:44:00 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lighting.h"

//               0              1           2                 3          4
// vs{point_light vector (vs[0]), r, point_camera vector (v), range, intensity}
t_p	diffuse_light(t_scene *s, t_p p, t_p n, t_obj *o)
{
	float		i;
	t_obj		*l;
	const t_obj	temp = (t_obj){.next = s->lights};
	t_p			vs[5];

	l = (t_obj *)&temp;
	i = 1;
	vs[4] = c_in((*s->ambient->color), *s->ambient->w);
	while (l->next)
	{
		l = l->next;
		sub(*l->p, p, &vs[0]);
		vs[3] = (t_p){.x = 0.01, .y = mag(vs[0])};
		norm(&vs[0]);
		if (calculate_ray(s, p, vs[0], &(vs[3])))
			continue ;
		vs[4] = c_add(vs[4], c_in((*l->color),
					(dot(n, vs[0]) > 0) * (*l->w * dot(n, vs[0]))));
		if (o->spec && *o->spec)
			i += (dot(*sub(*mult(*mult(n, 2, &(vs[1])), dot(n, vs[0]),
								&(vs[1])), vs[0], &(vs[1])), *sub(
							*s->camera->p, p, &(vs[2]))) > 0) * *l->w
				* powf(dot(vs[1], vs[2]) / mag(vs[1]) / mag(vs[2]), *o->spec);
	}
	return (vs[4]);
}

void	reflect_ray(t_p r, t_p n, t_p *ans)
{
	sub(*mult(*mult(n, 2, ans), dot(n, r), ans), r, ans);
}

t_p	get_reflect(t_scene *s, t_p p[2], t_p d, int depth)
{
	t_p			input[2];
	const t_p	range = (t_p){.x = 0.001, .y = FLT_MAX};

	mult(d, -1, &d);
	reflect_ray(d, p[1], &input[1]);
	input[0] = p[0];
	return (trace_ray(s, input, range, depth - 1));
}

// o_p, o_p2, per, n
// 0      1     2   3

typedef void	(*t_NORM)(t_obj, t_p, t_p*);
typedef void	(*t_CHECK)(t_obj, t_p, t_p, t_p*);
typedef void	(*t_M_IMG)(t_obj, t_img*, t_p, t_p*);

void	bump(t_obj o, t_p p, t_p *n, t_M_IMG get_c)
{
	t_p	c;
	t_p	tan;
	t_p	binormal;
	t_p	b_v;
	t_p	new_normal;

	get_c(o, o.b, p, &c);
	b_v = (t_p){.x = c_n(c.x), .y = c_n(c.y), .z = c_n(c.z)};
	tan = (t_p){.x = -n->z, 0, n->x};
	cross(*n, tan, &binormal);
	norm(&binormal);
	add(*mult(tan, b_v.x, &tan), *mult(binormal, b_v.y, &binormal),
		&new_normal);
	add(new_normal, *mult(*n, b_v.z, n), &new_normal);
	eq(n, new_normal);
	norm(n);
}

// p, n
// color, reflected
// p[0]: p
// p[1]: d
t_p	lighting(t_scene *s, t_obj o, t_p p[2], int depth)
{
	t_p				v[2];
	t_p				col[2];
	const t_NORM	norms[4] = {&sp_norm, &pl_norm, &cy_norm, &co_norm};
	const t_CHECK	checks[4] = {&sp_check, &pl_check, &cy_check, &co_check};
	const t_M_IMG	m_imgs[4] = {&sp_img, &pl_img, &cy_img, &co_img};

	add(p[0], p[1], &v[0]);
	norm(&p[1]);
	norms[*o.type](o, v[0], &v[1]);
	if (*o.type == PLANE && dot(*o.v, p[1]) > 0)
		norm(mult(v[1], -1, &v[1]));
	col[0] = *o.color;
	if (o.i)
		m_imgs[*o.type](o, o.i, v[0], &col[0]);
	if (o.dis && *o.dis == CHECKERBOARD)
		checks[*o.type](o, v[0], v[1], &col[0]);
	if (o.b)
		bump(o, v[0], &v[1], m_imgs[*o.type]);
	col[0] = (cl_mix((col[0]), diffuse_light(s, v[0], v[1], &o)));
	if (!depth || !o.reflect)
		return ((col[0]));
	col[1] = get_reflect(s, v, p[1], depth - 1);
	return (c_add(color_mult((col[0]), (1 - *o.reflect)),
			color_mult((col[1]), *o.reflect)));
}
