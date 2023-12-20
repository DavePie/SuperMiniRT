/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:57:09 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/20 17:02:17 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_H
# define LIGHTING_H
# include "structs.h"
# include "minirt.h"

float	lighting_sphere(t_scene *s, t_obj o, t_p d, int depth, float m);
float	lighting_cylinder(t_scene *s, t_obj o, t_p d, int depth, float m);
float	lighting_plane(t_scene *s, t_obj o, t_p d, int depth, float m);

#endif