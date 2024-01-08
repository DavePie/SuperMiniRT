/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:25:07 by dvandenb          #+#    #+#             */
/*   Updated: 2024/01/08 13:42:52 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

void			put_pixel(t_scene *s, int x, int y, t_p color);

t_p				color_mult(t_p color, float x);

t_p				cl_mix(t_p color1, t_p color2);

t_p				cls_add(t_p color1, t_p color2);

t_p				cls_intensity(t_p color, float intensity);

float			c_n(int color);

t_p				read_img(int x, int y, t_img *i);

#endif