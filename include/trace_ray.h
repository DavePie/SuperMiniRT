/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:29:25 by dvandenb          #+#    #+#             */
/*   Updated: 2024/01/08 18:40:08 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACE_RAY_H
# define TRACE_RAY_H
# include "structs.h"

void	trace_rays(t_scene *s);
int		calculate_shadow(t_scene *s, t_p p, t_p r, t_p *range);
t_obj	*calculate_ray(t_scene *s, t_p c, t_p r, t_p *range);
void	inter_ray_cylinder(t_p p, t_p r, t_obj *cyl, t_p *ans);
t_p		trace_ray(t_scene *s, t_p input[2], t_p range, int depth);
void	check_cylinder_caps(t_p p, t_p r, t_obj *cyl, t_p *ans);
float	intersect_plane(t_p p, t_p r, t_p plane_p, t_p plane_normal);

void	inter_ray_plane(t_p p, t_p r, t_obj *plane, t_p *ans);
void	inter_ray_sphere(t_p p, t_p r, t_obj *sphere, t_p *ans);
void	inter_ray_cone(t_p p, t_p r, t_obj *cone, t_p *ans);

#endif