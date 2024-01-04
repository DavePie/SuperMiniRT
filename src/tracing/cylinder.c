/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:56:01 by dvandenb          #+#    #+#             */
/*   Updated: 2024/01/04 17:54:43 by dvandenb         ###   ########.fr       */
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

void	cy_img(t_obj o, t_img *i, t_p p, t_p *c)
{
	(void)o, (void)i, (void)p, (void)c;
}

void	cy_check(t_obj o, t_p p, t_p n, t_p *color)
{
	t_p		vec_x;
	float	angle;
	int		x;
	int		y;

	y = 0;
	vec_x = (t_p){.x = o.v->z, .z = -o.v->x};
	if (!o.v->z && !o.v->x)
		vec_x = (t_p){.x = 1};
	if (dot(n, *o.v))
	{
		pl_check(o, p, n, color);
		return ;
	}
	angle = acosf(dot(*norm(&vec_x), n));
	if (angle < 0)
		angle += 2 * M_PI;
	if (dot(n, vec_x) < 0)
		angle += M_PI / 4;
	x = (int)(angle / M_PI / 2 * 1000);
	if ((x % 100 > 50 && y % 1000 > 500) || (x % 100 < 50 && y % 1000 < 500))
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
