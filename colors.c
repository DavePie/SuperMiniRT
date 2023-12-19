/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:16:27 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/19 14:52:20 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minirt.h"

void	put_pixel(t_scene *s, int x, int y, unsigned int color)
{
	char		*pix;
	const int	w = s->mlx->width;

	pix = s->mlx->pix;
	pix[(x + y * w) * 4 + 0] = color  & 0xFF;
	pix[(x + y * w) * 4 + 1] = color >> 8 & 0xFF;
	pix[(x + y * w) * 4 + 2] = color >> 16 & 0xFF;
	pix[(x + y * w) * 4 + 3] = color >> 24 & 0xFF;
}

void	whiten(unsigned int *a, unsigned int *b, unsigned int *c)
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

unsigned int	color_mult(unsigned int color, float x)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = (color >> 16) * x;
	g = (color >> 8) % 256 * x;
	b = (color) % 256 * x;
	whiten(&r, &g, &b);
	whiten(&g, &r, &b);
	whiten(&b, &g, &r);
	return ((r << 16) + (g << 8) + (b));
}

unsigned int	cl(int r, int g, int b)
{
	if (r < 0)
		r += 255;
	if (g < 0)
		g += 255;
	if (b < 0)
		b += 255;
	return ((r << 16 ) | (g << 8 ) | (b ));
}