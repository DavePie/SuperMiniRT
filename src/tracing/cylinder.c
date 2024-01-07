/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:56:01 by dvandenb          #+#    #+#             */
/*   Updated: 2024/01/07 23:40:44 by alde-oli         ###   ########.fr       */
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
	}
	norm(n);
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
			* (cp.z - proj.z)) / *o.w * cos(angle) / 2 + 0.5;
	*y = sqrt((cp.x - proj.x) * (cp.x - proj.x) + (cp.z - proj.z)
			* (cp.z - proj.z)) / *o.w * sin(angle) / 2 + 0.5;
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
	if (fabs(y - 0) < 0.01 || fabs(y - 1) < 0.01)
		coords_caps(o, cp, &x, &y);
	pix_x = x * (i->w - 1);
	pix_y = (1 - y) * (i->h - 1);
	if (fabs(y - 0) < 0.01 || fabs(y - 1) < 0.01
		|| pix_x + pix_y * i->w >= i->w * i->h)
		return ;
	*c = (t_p){.x = i->pix[(pix_x + pix_y * i->w) * 4 + 2],
		.y = i->pix[(pix_x + pix_y * i->w) * 4 + 1],
		.z = i->pix[(pix_x + pix_y * i->w) * 4]};
}

//not working well for caps
void	cy_check(t_obj o, t_p p, t_p n, t_p *color)
{
	t_p		cp;
	float	x;
	float	y;
	int		check;

	(void) n;
	cp = (t_p){p.x - o.p->x, p.y - o.p->y, p.z - o.p->z};
	coords_body(o, cp, &x, &y);
	if (fabs(y - 0) < 0.01 || fabs(y - 1) < 0.01)
	{
		x = cp.x;
		y = cp.z;
	}
	check = ((int)(x * 10) % 2 == 0) ^ ((int)(y * 10) % 2 == 0);
	if (check)
		*color = (color_mult((*color), 1.2));
	else
		*color = (color_mult((*color), 0.8));

}

// void	apply_checker_board_cyl(t_obj o, t_p p, t_p n, unsigned int *color)
// {
// 	t_p		temp;
// 	t_p		vec;
// 	float	angle;
// 	int		x;
// 	int		y;

// 	if (dot(n, *o.v))
// 	{
// 		//pl_check(o, p, color);
// 		return ;
// 	}
// 	temp = (t_p){.x = o.v->z, .z = -o.v->x};
// 	if (!o.v->z && !o.v->x)
// 		temp = (t_p){.x = o.v->y, .y = -o.v->x};
// 	norm(sub(p, *o.p, &vec));
// 	norm(&temp);
// 	angle = acosf(dot(n, temp));
// 	if (angle < 0)
// 		angle += M_PI * 2;
// 	x = (int)(angle / M_PI / 2 * 1000);
// 	y = 0;
// 	if ((x % 100 > 50 && y % 100 > 50) || (x % 100 < 50 && y % 100 < 50))
// 		*color = cll(color_mult(cl_split(*color), 1.2));
// 	else
// 		*color = cll(color_mult(cl_split(*color), 0.8));
// }
