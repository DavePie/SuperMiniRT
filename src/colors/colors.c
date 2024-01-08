/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:16:27 by dvandenb          #+#    #+#             */
/*   Updated: 2024/01/08 13:47:36 by dvandenb         ###   ########.fr       */
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

t_p	cl_split(unsigned int color)
{
	return ((t_p){.x = (color >> 16) & 0xFF,
		.y = (color >> 8) & 0xFF, .z = color & 0xFF});
}

t_p	cl_mix(t_p obj, t_p intensity)
{
	return ((t_p){.x = fmin((obj.x * intensity.x), obj.x),
		.y = fmin((obj.y * intensity.y), obj.y),
		.z = fmin((obj.z * intensity.z), obj.z)});
}

t_p	cls_intensity(t_p color, float intensity)
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

float	c_n(int color)
{
	if (color < 0)
		color += 255;
	return ((float)color / 255 - 0.5);
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
