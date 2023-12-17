/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:57:09 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/17 23:43:15 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_H
# define LIGHTING_H
# include "structs.h"
# include "minirt.h"

float	lighting_sphere(t_scene *s, t_obj o, t_p d, float m);
float	lighting_cylinder(t_scene *s, t_obj o, t_p d, float m);

#endif