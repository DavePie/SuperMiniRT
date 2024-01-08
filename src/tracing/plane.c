/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:03:42 by dvandenb          #+#    #+#             */
/*   Updated: 2024/01/08 15:49:28 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lighting.h"

void	pl_norm(t_obj o, t_p p, t_p *n)
{
	(void)p;
	eq(n, *o.v);
}

void	pl_img(t_obj o, t_img *i, t_p p, t_p *c)
{
	(void)o, (void)i, (void)p, (void)c;
}

void	pl_check(t_obj o, t_p p, t_p n, t_p *color)
{
	t_p	vec;
	t_p	vec_x;
	t_p	vec_y;
	t_p	vals;
	int	axis[2];

	(void)n;
	sub(p, *o.p, &vec);
	vec_x = (t_p){.x = o.v->z, .z = -o.v->x};
	if (!o.v->z && !o.v->x)
		vec_x = (t_p){.x = 1, .z = 0};
	norm(&vec_x);
	norm(cross(*o.v, vec_x, &vec_y));
	vals = solve_vecs(vec_x, vec_y, p);
	axis[1] = vals.y * 1000;
	axis[0] = vals.x * 1000;
	axis[1] = (axis[1] >= 0) * axis[1] + ((axis[1] < 0) * (-axis[1] + 500));
	axis[0] = (axis[0] >= 0) * axis[0] + ((axis[0] < 0) * (-axis[0] + 500));
	if ((axis[1] % 1000 > 500 && axis[0] % 1000 > 500)
		|| (axis[1] % 1000 < 500 && axis[0] % 1000 < 500))
		*color = (color_mult((*color), 0.8));
	else
		*color = (color_mult((*color), 1.2));
}
