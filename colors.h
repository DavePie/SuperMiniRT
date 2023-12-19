/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:25:07 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/18 14:24:19 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

void			put_pixel(t_scene *s, int x, int y, unsigned int color);

unsigned int	color_mult(unsigned int color, float x);

unsigned int	cl(int r, int g, int b);

#endif