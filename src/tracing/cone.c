/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:10:39 by dvandenb          #+#    #+#             */
/*   Updated: 2024/01/04 16:13:32 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lighting.h"

void	co_norm(t_obj o, t_p p, t_p *n)
{
	t_p	v[4];

	sub(p, *o.p, &v[0]);
	eq(&v[1], v[0]);
	norm(&v[0]);
	cross(v[0], *norm(o.v), &v[2]);
	cross(v[0], v[2], n);
	norm(n);
	if (mag(v[1]) >= *o.h && fabs(acosf(dot(v[0], *o.v))
			- atanf(*o.w / *o.h / 2)) > 0.001)
		eq(n, *o.v);
}

void	co_img(t_obj o, t_img *i, t_p p, t_p *c)
{
	(void)o, (void)i, (void)p, (void)c;
}

void	co_check(t_obj o, t_p p, t_p *color)
{
	(void)o, (void)p, (void)color;
}
