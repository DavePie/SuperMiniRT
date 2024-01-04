/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:46:22 by dvandenb          #+#    #+#             */
/*   Updated: 2024/01/03 17:40:36 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "lighting.h"

typedef void	(*t_NORM)(t_obj, t_p, t_p*);
typedef void	(*t_M_IMG)(t_obj, t_p, t_c*);
typedef void	(*t_BMP)(t_obj, t_p, t_p*);

void	sp_norm(t_obj o, t_p p, t_p *n)
{
	norm(sub(p, *o.p, n));
}

void	sp_map_img(t_obj o, t_img *i, t_p p, t_p *c)
{
	t_p	vec;
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
	*c = (t_p){.x = i->pix[(x + y * i->w) * 4 + 2],
		.y = i->pix[(x + y * i->w) * 4 + 1],
		.z = i->pix[(x + y * i->w) * 4]};
}

void	sp_img(t_obj o, t_p p, t_p *c)
{
	sp_map_img(o, o.i, p, c);
}

//void	sp_