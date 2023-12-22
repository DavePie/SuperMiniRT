/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:16:27 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/22 15:40:20 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minirt.h"

void	put_pixel(t_scene *s, int x, int y, unsigned int color)
{
	char		*pix;
	const int	w = s->mlx->width;

	pix = s->mlx->pix;
	pix[(x + y * w) * 4 + 0] = color & 0xFF;
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

unsigned int	cl(int r, int g, int b)
{
	if (r < 0)
		r += 255;
	if (g < 0)
		g += 255;
	if (b < 0)
		b += 255;
	return ((r << 16) | (g << 8) | (b));
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

t_c	cl_split(unsigned int color)
{
	return ((t_c){.x = (color >> 16) & 0xFF,
		.y = (color >> 8) & 0xFF, .z = color & 0xFF});
}

unsigned int	cl_mix(unsigned int obj, t_p intensity)
{
	t_c	int1;

	int1 = cl_split(obj);

	return (cl(fmin((int1.x * intensity.x), int1.x), fmin((int1.y * intensity.y), int1.y),
			fmin((int1.z * intensity.z), int1.z)));
}

t_p	cls_intensity(t_c color, float intensity)
{
	t_p	result;

	result.x = color.x / 255 * intensity;
	result.y = color.y / 255 * intensity;
	result.z = color.z / 255 * intensity;
	return (result);
}

t_p	cls_add(t_p color1, t_p color2)
{
	return ((t_p){.x = fmin((color1.x + color2.x), 255),
		.y = fmin((color1.y + color2.y), 255),
		.z = fmin((color1.z + color2.z), 255)});
}
