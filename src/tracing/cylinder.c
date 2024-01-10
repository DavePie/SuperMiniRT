/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:56:01 by dvandenb          #+#    #+#             */
/*   Updated: 2024/01/10 14:35:01 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lighting.h"

void	cy_norm(t_obj o, t_p p, t_p *n)
{
	const t_p	cp = {p.x - o.p->x, p.y - o.p->y, p.z - o.p->z};
	const float	proj_l = dot(cp, *o.v);
	const float	ep = 0.001;
	t_p			proj;

	if (fabs(proj_l) < ep)
		*n = ((t_p){-o.v->x, -o.v->y, -o.v->z});
	else if (fabs(proj_l - *o.h) < ep)
		*n = ((t_p){o.v->x, o.v->y, o.v->z});
	else
	{
		proj = (t_p){proj_l * o.v->x,
			proj_l * o.v->y, proj_l * o.v->z};
		*n = (t_p){cp.x - proj.x, cp.y - proj.y, cp.z - proj.z};
		norm(n);
	}
}

void	coords_body(t_obj o, t_p cp, float *x, float *y)
{
	const t_p	proj = {dot(cp, *o.v) * o.v->x, dot(cp, *o.v)
		* o.v->y, dot(cp, *o.v) * o.v->z};
	t_p			ref_vector;
	t_p			perp_vector;
	t_p			cross_product;
	float		angle;

	if (fabs(o.v->x) < 0.5)
		ref_vector = (t_p){1, 0, 0};
	else
		ref_vector = (t_p){0, 1, 0};
	cross(*o.v, ref_vector, &perp_vector);
	cross(*o.v, (t_p){cp.x - proj.x, cp.y - proj.y, cp.z - proj.z},
		&cross_product);
	angle = atan2f(dot(cross_product, perp_vector), dot((t_p){cp.x
				- proj.x, cp.y - proj.y, cp.z - proj.z}, perp_vector));
	if (angle < 0)
		angle += 2 * M_PI;
	*x = angle / (2 * M_PI);
	*y = dot(proj, *o.v) / *o.h;
}

void	coords_caps(t_obj o, t_p cp, float *x, float *y)
{
	const t_p	proj = {dot(cp, *o.v) * o.v->x, dot(cp, *o.v)
		* o.v->y, dot(cp, *o.v) * o.v->z};
	t_p			ref_vector;
	t_p			perp_vector;
	t_p			cross_product;
	float		angle;

	if (fabs(o.v->x) < 0.5)
		ref_vector = (t_p){1, 0, 0};
	else
		ref_vector = (t_p){0, 1, 0};
	cross(*o.v, ref_vector, &perp_vector);
	cross(*o.v, (t_p){cp.x - proj.x, cp.y - proj.y,
		cp.z - proj.z}, &cross_product);
	angle = atan2f(dot(cross_product, perp_vector), dot((t_p){cp.x
				- proj.x, cp.y - proj.y, cp.z - proj.z}, perp_vector));
	if (angle < 0)
		angle += 2 * M_PI;
	*x = sqrt((cp.x - proj.x) * (cp.x - proj.x) + (cp.z - proj.z)
			* (cp.z - proj.z)) / *o.w * cos(angle) + 0.5;
	*y = sqrt((cp.x - proj.x) * (cp.x - proj.x) + (cp.z - proj.z)
			* (cp.z - proj.z)) / *o.w * sin(angle) + 0.5;
}

void	cy_img(t_obj o, t_img *i, t_p p, t_p *c)
{
	t_p		cp;
	float	x;
	float	y;
	int		pix_x;
	int		pix_y;

	cp = (t_p){p.x - o.p->x, p.y - o.p->y, p.z - o.p->z};
	coords_body(o, cp, &x, &y);
	if (fabs(y - 0) < 0.0001 || fabs(y - 1) < 0.0001)
		coords_caps(o, cp, &x, &y);
	pix_x = x * (i->w);
	pix_y = (1 - y) * (i->h);
	if (pix_x + pix_y * i->w >= i->w * i->h)
		return ;
	*c = read_img(pix_x, pix_y, i);
}

void	cy_check(t_obj o, t_p p, t_p n, t_p *color)
{
	t_p		cp;
	float	x;
	float	y;
	int		check;

	cp = (t_p){p.x - o.p->x, p.y - o.p->y, p.z - o.p->z};
	if ((n.x == o.v->x && n.y == o.v->y && n.z == o.v->z)
		|| (n.x == -o.v->x && n.y == -o.v->y && n.z == -o.v->z))
	{
		pl_check(o, p, n, color);
		return ;
	}
	coords_body(o, cp, &x, &y);
	check = ((int)(x * (*o.w * 2)) % 2 == 0)
		^ ((int)(y * (*o.h / (M_PI / 4))) % 2 == 0);
	if (check)
		*color = color_mult((*color), 1.2);
	else
		*color = color_mult((*color), 0.8);
}
