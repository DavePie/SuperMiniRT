/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:29:25 by dvandenb          #+#    #+#             */
/*   Updated: 2024/01/04 13:17:36 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACE_RAY_H
# define TRACE_RAY_H
# include "structs.h"

void			trace_rays(t_scene *s);
int				calculate_shadow(t_scene *s, t_p p, t_p r, t_p *range);
t_obj			*calculate_ray(t_scene *s, t_p c, t_p r, t_p *range);
void			inter_ray_cylinder(t_p p, t_p r, t_obj *cyl, t_p *ans);
unsigned int	trace_ray(t_scene *s, t_p r, t_p range, int depth);
void			check_cylinder_caps(t_p p, t_p r, t_obj *cyl, t_p *ans);
float	intersect_plane(t_p p, t_p r, t_p plane_p, t_p plane_normal);

#endif