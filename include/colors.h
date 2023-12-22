/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:25:07 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/22 15:40:11 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

void			put_pixel(t_scene *s, int x, int y, unsigned int color);

unsigned int	cl(int r, int g, int b);

unsigned int	color_mult(unsigned int color, float x);

t_c				cl_split(unsigned int color);

unsigned int	cl_mix(unsigned int color1, t_p color2);

t_p				cls_add(t_p color1, t_p color2);

t_p				cls_intensity(t_c color, float intensity);

#endif