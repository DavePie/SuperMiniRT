/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:16:27 by dvandenb          #+#    #+#             */
/*   Updated: 2024/01/08 17:57:22 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minirt.h"

void	put_pixel(t_scene *s, int x, int y, t_p color)
{
	char		*pix;
	const int	w = s->mlx->width;

	pix = s->mlx->pix;
	pix[(x + y * w) * 4 + 0] = (int)color.z;
	pix[(x + y * w) * 4 + 1] = (int)color.y;
	pix[(x + y * w) * 4 + 2] = (int)color.x;
}
//pix[(x + y * w) * 4 + 3] = color >> 24 & 0xFF;

void	whiten(float *a, float *b, float *c)
{
	if (*a >= 256)
	{
		*b = (*b + (*a - 256));
		*c = (*c + (*a - 256));
		*a = 255;
		if (*b > 255)
			*b = 255;
		if (*c > 255)
			*c = 255;
	}
}

t_p	color_mult(t_p color, float x)
{
	t_p	ans;

	ans.x = color.x * x;
	ans.y = color.y * x;
	ans.z = color.z * x;
	whiten(&ans.x, &ans.y, &ans.z);
	whiten(&ans.y, &ans.x, &ans.z);
	whiten(&ans.z, &ans.y, &ans.x);
	return (ans);
}

t_p	read_img(int x_p, int y_p, t_img *i)
{
	int	x;
	int	y;
	int	z;

	x = i->pix[(x_p + y_p * i->w) * 4 + 2];
	y = i->pix[(x_p + y_p * i->w) * 4 + 1];
	z = i->pix[(x_p + y_p * i->w) * 4];
	x += (x < 0) * 255;
	y += (y < 0) * 255;
	z += (z < 0) * 255;
	return ((t_p){.x = x, .y = y, .z = z});
}
