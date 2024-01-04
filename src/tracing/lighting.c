/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:35:08 by dvandenb          #+#    #+#             */
/*   Updated: 2024/01/04 13:29:37 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lighting.h"

//               0              1           2                 3
// vs{point_light vector (vs[0]), r, point_camera vector (v), range}
t_p	diffuse_light(t_scene *s, t_p p, t_p n, t_obj *o)
{
	float		i;
	t_p			intensity;
	t_obj		*l;
	t_p			vs[4];

	i = 1;
	intensity = cls_intensity(cl_split(*s->ambient->color), *s->ambient->w);
	l = s->lights;
	while (l)
	{
		sub(*l->p, p, &vs[0]);
		vs[3] = (t_p){.x = 0.01, .y = mag(vs[0])};
		norm(&vs[0]);
		if (calculate_ray(s, p, vs[0], &(vs[3])))
		{
			l = l->next;
			continue ;
		}
		intensity = cls_add(intensity, cls_intensity(cl_split(*l->color), (dot(n, vs[0]) > 0) * (*l->w * dot(n, vs[0]))));
		if (o->specular && *o->specular)
			i += (dot(*sub(*mult(*mult(n, 2, &(vs[1])), dot(n, vs[0]), &(vs[1])), vs[0], &(vs[1])), *sub(*s->camera->p, p, &(vs[2]))) > 0) * *l->w * powf(dot(vs[1], vs[2]) / mag(vs[1]) / mag(vs[2]), *o->specular);
		l = l->next;
	}
	return (intensity);
}

int	create_trgb(unsigned char t, unsigned char r,
	unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

t_c	*map_sphere_img_(t_obj o, t_img *i, t_p vec, t_c *col)
{
	float	angle;
	int		x;
	int		y;

	angle = atanf(vec.z / vec.x) + (vec.x < 0) * (M_PI);
	if (angle < 0)
		angle += M_PI * 2;
	if (angle > M_PI * 2)
		angle -= M_PI * 2;
	x = (int)(angle / M_PI / 2 * i->w);
	y = (vec.y + (*o.w / 2)) / *o.w * i->h;
	*col = (t_c){.x = i->pix[(x + y * i->w) * 4 + 2],
		.y = i->pix[(x + y * i->w) * 4 + 1],
		.z = i->pix[(x + y * i->w) * 4]};
	return (col);
}

void	apply_checker_board_plane(t_p v, t_p p_o, t_p p, unsigned int *color)
{
	t_p		vec;
	t_p		vec_x;
	t_p		vec_y;
	int		set_col;
	int		set_row;

	sub(p, p_o, &vec);
	vec_x = (t_p){.x = v.z, .z = -v.x};
	if (!v.z && !v.x)
		vec_x = (t_p){.x = 1, .z = 0};
	norm(cross(v, vec_x, &vec_y));
	norm(&vec_x);
	set_col = (vec.y / vec_y.y) * 1000;
	if (!vec_y.y)
		set_col = (vec.z / vec_y.z) * 1000;
	set_row = ((vec.x - ((float)(set_col) * vec_y.x)) / vec_x.x) * 1000;
	if (!vec_x.x)
		set_row = ((vec.z - ((float)(set_col) * vec_y.z)) / vec_x.z) * 1000;
	set_col = (set_col >= 0) * set_col + ((set_col < 0) * (-set_col + 500));
	set_row = (set_row >= 0) * set_row + ((set_row < 0) * (-set_row + 500));
	if ((set_col % 1000 > 500 && set_row % 1000 > 500)
		|| (set_col % 1000 < 500 && set_row % 1000 < 500))
		*color = color_mult(*color, 0.8);
	else
		*color = color_mult(*color, 1.2);
}

void	apply_checker_board_cyl(t_obj o, t_p p, t_p n, unsigned int *color)
{
	t_p		temp;
	t_p		vec;
	float	angle;
	int		x;
	int		y;

	if (dot(n, *o.v))
	{
		apply_checker_board_plane(*o.v, *o.p, p, color);
		return ;
	}
	temp = (t_p){.x = o.v->z, .z = -o.v->x};
	if (!o.v->z && !o.v->x)
		temp = (t_p){.x = o.v->y, .y = -o.v->x};
	norm(sub(p, *o.p, &vec));
	norm(&temp);
	angle = acosf(dot(n, temp));
	if (angle < 0)
		angle += M_PI * 2;
	x = (int)(angle / M_PI / 2 * 1000);
	y = 0;
	if ((x % 100 > 50 && y % 100 > 50) || (x % 100 < 50 && y % 100 < 50))
		*color = color_mult(*color, 1.2);
	else
		*color = color_mult(*color, 0.8);
}

void	apply_checker_board_sphere(t_p vec, unsigned int *color)
{
	float		angle;
	float		angle2;
	int			x;
	int			y;
	const t_p	temp = (t_p){.x = vec.x, .z = vec.z};

	angle = atanf(vec.z / vec.x) + (vec.x < 0) * (M_PI);
	if (angle < 0)
		angle += M_PI * 2;
	angle2 = atanf((mag(temp) / vec.y)) + (vec.y < 0) * (M_PI);
	if (angle2 < 0)
		angle2 += M_PI * 2;
	x = (int)(angle / M_PI / 2 * 1000);
	y = (int)(angle2 / M_PI / 2 * 1000);
	if ((x % 100 > 50 && y % 100 > 50) || (x % 100 < 50 && y % 100 < 50))
		*color = color_mult(*color, 1.2);
	else
		*color = color_mult(*color, 0.8);
}

unsigned int	map_sphere_img(t_obj o, t_p vec)
{
	t_c	c;

	map_sphere_img_(o, o.i, vec, &c);
	return (cl(c.x, c.y, c.z));
}

float	c_n(int color)
{
	if (color < 0)
		color += 255;
	return ((float)color / 255 - 0.5);
}

void	map_sphere_bmp(t_obj o, t_p vec, t_p *n)
{
	t_c	c;
	t_p	tan;
	t_p	binormal;
	t_p	b_v;
	t_p	new_normal;

	map_sphere_img_(o, o.b, vec, &c);
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

void	reflect_ray(t_p r, t_p n, t_p *ans)
{
	sub(*mult(*mult(n, 2, ans), dot(n, r), ans), r, ans);
}

float	get_reflect(t_scene *s, t_p n, t_p d, int depth)
{
	t_p			r;
	const t_p	range = (t_p){.x = 0.001, .y = FLT_MAX};

	mult(d, -1, &d);
	reflect_ray(d, n, &r);
	return (trace_ray(s, r, range, depth - 1));
}

float	lighting_sphere(t_scene *s, t_obj o, t_p d, int depth)
{
	const t_p		p = (t_p){.x = s->camera->p->x + ( d.x),
		.y = s->camera->p->y + (d.y), .z = s->camera->p->z + ( d.z)};
	t_p				n;
	t_p				vec;
	unsigned int	color;
	unsigned int	reflected;

	norm(&d);
	sub(p, *o.p, &vec);
	color = *o.color;
	norm(sub(p, *o.p, &n));
	if (o.i)
		color = map_sphere_img(o, vec);
	if (o.b)
		map_sphere_bmp(o, vec, &n);
	if (o.distrupt && *o.distrupt == CHECKERBOARD)
		apply_checker_board_sphere(vec, &color);
	color = cl_mix(color, diffuse_light(s, p, n, &o));

	if (!depth || !o.reflect)
		return (color);
	reflected = get_reflect(s, n, d, depth - 1);
	return (color_mult(color, (1 - *o.reflect))
		+ color_mult(reflected, *o.reflect));
}

void	calculate_cylinder_normal(t_obj o, t_p p, t_p *n)
{
	const t_p	cp = {p.x - o.p->x, p.y - o.p->y, p.z - o.p->z};
	const float	proj_l = dot(cp, *o.v);
	const float	ep = 0.001;
	t_p			proj;
	t_p			normal;

	if (fabs(proj_l) < ep)
		*n = ((t_p){-o.v->x, -o.v->y, -o.v->z});
	else if (fabs(proj_l - *o.h) < ep)
		*n = ((t_p){o.v->x, o.v->y, o.v->z});
	else
	{
		proj = (t_p){proj_l * o.v->x,
			proj_l * o.v->y, proj_l * o.v->z};
		normal = (t_p){cp.x - proj.x, cp.y - proj.y, cp.z - proj.z};
		norm(&normal);
		*n = normal;
	}
}

float	lighting_cylinder(t_scene *s, t_obj o, t_p d, int depth)
{
	const t_p		p = (t_p){.x = s->camera->p->x + (d.x),
		.y = s->camera->p->y + (d.y),
		.z = s->camera->p->z + (d.z)};
	t_p				n;
	unsigned int	reflected;
	unsigned int	color;

	norm(&d);
	calculate_cylinder_normal(o, p, &n);
	norm(&n);
	color = (cl_mix(*o.color, diffuse_light(s, p, n, &o)));
	if (o.distrupt && *o.distrupt)
		apply_checker_board_cyl(o, p, n, &color);
	if (!depth || !o.reflect)
		return (color);
	reflected = get_reflect(s, n, d, depth - 1);
	return (color_mult(color, (1 - *o.reflect))
		+ color_mult(reflected, *o.reflect));
}

float	lighting_plane(t_scene *s, t_obj o, t_p d, int depth)
{
	const t_p		c = *s->camera->p;
	const t_p		p = (t_p){.x = c.x + (d.x), .y = c.y + (d.y),
		.z = c.z + d.z};
	unsigned int	reflected;
	unsigned int	color;

	norm(&d);
	if (dot(*o.v, d) > 0)
		norm(mult(*o.v, -1, o.v));
	color = (cl_mix(*o.color, diffuse_light(s, p, *o.v, &o)));
	if (o.distrupt && *o.distrupt == CHECKERBOARD)
		apply_checker_board_plane(*o.v, *o.p, p, &color);
	if (!depth || !o.reflect || !*o.reflect)
		return (color);
	reflected = get_reflect(s, *o.v, d, depth - 1);
	return (color_mult(color, (1 - *o.reflect))
		+ color_mult(reflected, *o.reflect));
}

// o_p, o_p2, per, n
// 0      1     2   3

typedef void	(*t_NORM)(t_obj, t_p, t_p*);
typedef void	(*t_M_IMG)(t_obj, t_p, t_c*);
typedef void	(*t_BMP)(t_obj, t_p, t_p*);

// p, n
// color, reflected
// float	lighting(t_scene *s, t_obj o, t_p d, int depth)
// {
// 	t_p				v[2];
// 	t_p				col[2];
// 	const t_NORM	norms[4] = {&sp_norm, &pl_norm, &cy_norm, &co_norm,
// 		&sp_bmp, &pl_bmp, &cy_bmp, &co_bmp};
// 	const t_M_IMG	m_imgs[8] = {&sp_img, &pl_img, &cy_img, &co_img,
// 		&sp_check, &pl_check, &cy_check, &co_check};

// 	add(*s->camera->p, d, &v[0]);
// 	norm(&d);
// 	norms[*o.type](o, v[0], &v[1]);
// 	if (o.b)
// 		norms[*o.type + 4](o, v[0], &v[1]);
// 	if (o.i)
// 		m_imgs[*o.type](o, v[0], &col[0]);
// 	if (o.distrupt && *o.distrupt == CHECKERBOARD)
// 		m_imgs[*o.type + 4](o, v[0], &col[0]);
// 	col[0] = (cl_mix(*o.color, diffuse_light(s, v[0], v[1], &o)));
// 	if (!depth || !o.reflect)
// 		return (col[0]);
// 	col[1] = get_reflect(s, v[1], d, depth - 1);
// 	return (color_mult(col[0], (1 - *o.reflect))
// 		+ color_mult(col[1], *o.reflect));
// }

float	lighting_cone(t_scene *s, t_obj o, t_p d, int depth)
{
	const t_p		p = (t_p){.x = s->camera->p->x + (d.x),
		.y = s->camera->p->y + (d.y),
		.z = s->camera->p->z + (d.z)};
	t_p				n;
	t_p				v[4];
	unsigned int		reflected;
	unsigned int		color;

	sub(p, *o.p, &v[0]);
	eq(&v[1], v[0]);
	norm(&d);
	norm(&v[0]);
	cross(v[0], *norm(o.v), &v[2]);
	cross(v[0], v[2], &n);
	norm(&n);
	if (mag(v[1]) >= *o.h && fabs(acosf(dot(v[0], *o.v)) - atanf(*o.w / *o.h / 2)) > 0.001)
		eq(&n, *o.v);
	color = (cl_mix(*o.color, diffuse_light(s, p, n, &o)));
	// if (o.distrupt && *o.distrupt)
	// 	apply_checker_board_cyl(o, p, n, &color);
	if (!depth || !o.reflect)
		return (color);
	reflected = get_reflect(s, n, d, depth - 1);
	return (color_mult(color, (1 - *o.reflect))
		+ color_mult(reflected, *o.reflect));
}
