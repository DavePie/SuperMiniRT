/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:55:44 by dvandenb          #+#    #+#             */
/*   Updated: 2024/01/08 18:01:48 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minirt.h"

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

t_p	c_in(t_p color, float intensity)
{
	t_p	result;

	result.x = color.x / 255 * intensity;
	result.y = color.y / 255 * intensity;
	result.z = color.z / 255 * intensity;
	return (result);
}

t_p	c_add(t_p color1, t_p color2)
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
