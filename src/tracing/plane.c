/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:03:42 by dvandenb          #+#    #+#             */
/*   Updated: 2024/01/08 15:53:37 by alde-oli         ###   ########.fr       */
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
	t_p		vec;
	t_p		vec_x;
	t_p		vec_y;
	int		set_col;
	int		set_row;

	sub(p, *o.p, &vec);
	vec_x = (t_p){.x = o.v->z, .z = -o.v->x};
	if (!o.v->z && !o.v->x)
		vec_x = (t_p){.x = 1, .z = 0};
	norm(cross(*o.v, vec_x, &vec_y));
	norm(&vec_x);
	set_col = (vec.y / vec_y.y) * 100;
	if (!vec_y.y)
		set_col = (vec.z / vec_y.z) * 100;
	set_row = ((vec.x - (((float)(set_col)) * vec_y.x)) / vec_x.x) * 100;
	if (!vec_x.x)
		set_row = ((vec.z - (((float)(set_col)) * vec_y.z)) / vec_x.z) * 100;
	set_col = (set_col >= 0) * set_col + ((set_col < 0) * (-set_col + 500));
	set_row = (set_row >= 0) * set_row + ((set_row < 0) * (-set_row + 500));
	set_col %= i->w;
	set_row %= i->h;
	*c = (t_p){.x = i->pix[(set_col + set_row * i->w) * 4 + 2],
		.y = i->pix[(set_col + set_row * i->w) * 4 + 1],
		.z = i->pix[(set_col + set_row * i->w) * 4]};
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
