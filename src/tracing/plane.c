/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:03:42 by dvandenb          #+#    #+#             */
/*   Updated: 2024/01/04 17:14:13 by dvandenb         ###   ########.fr       */
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
	t_p		vec;
	t_p		vec_x;
	t_p		vec_y;
	int		set_col;
	int		set_row;

	(void)n;
	sub(p, *o.p, &vec);
	vec_x = (t_p){.x = o.v->z, .z = -o.v->x};
	if (!o.v->z && !o.v->x)
		vec_x = (t_p){.x = 1, .z = 0};
	norm(cross(*o.v, vec_x, &vec_y));
	norm(&vec_x);
	set_col = (vec.y / vec_y.y) * 1000;
	if (!vec_y.y)
		set_col = (vec.z / vec_y.z) * 1000;
	set_row = ((vec.x - (((float)(set_col)) * vec_y.x)) / vec_x.x) * 1000;
	if (!vec_x.x)
		set_row = ((vec.z - (((float)(set_col)) * vec_y.z)) / vec_x.z) * 1000;
	set_col = (set_col >= 0) * set_col + ((set_col < 0) * (-set_col + 500));
	set_row = (set_row >= 0) * set_row + ((set_row < 0) * (-set_row + 500));
	if ((set_col % 1000 > 500 && set_row % 1000 > 500)
		|| (set_col % 1000 < 500 && set_row % 1000 < 500))
		*color = (color_mult((*color), 0.8));
	else
		*color = (color_mult((*color), 1.2));
}
