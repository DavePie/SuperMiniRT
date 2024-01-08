/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:46:22 by dvandenb          #+#    #+#             */
/*   Updated: 2024/01/08 13:44:52 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lighting.h"

void	sp_norm(t_obj o, t_p p, t_p *n)
{
	norm(sub(p, *o.p, n));
}

void	sp_img(t_obj o, t_img *i, t_p p, t_p *c)
{
	t_p		vec;
	float	angle;
	int		x;
	int		y;

	sub(p, *o.p, &vec);
	angle = atanf(vec.z / vec.x) + (vec.x < 0) * (M_PI);
	if (angle < 0)
		angle += M_PI * 2;
	if (angle > M_PI * 2)
		angle -= M_PI * 2;
	x = (int)(angle / M_PI / 2 * i->w);
	y = (vec.y + (*o.w / 2)) / *o.w * i->h;
	*c = read_img(x, y, i);
}

void	sp_check(t_obj o, t_p p, t_p n, t_p *color)
{
	float		angle;
	float		angle2;
	int			x;
	int			y;
	const t_p	temp = (t_p){.x = n.x, .z = n.z};

	(void) p, (void) o;
	angle = atanf(n.z / n.x) + (n.x < 0) * (M_PI);
	if (angle < 0)
		angle += M_PI * 2;
	angle2 = atanf((mag(temp) / n.y)) + (n.y < 0) * (M_PI);
	if (angle2 < 0)
		angle2 += M_PI * 2;
	x = (int)(angle / M_PI / 2 * 1000);
	y = (int)(angle2 / M_PI / 2 * 1000);
	if ((x % 100 > 50 && y % 100 > 50) || (x % 100 < 50 && y % 100 < 50))
		*color = (color_mult((*color), 1.2));
	else
		*color = (color_mult((*color), 0.8));
}
