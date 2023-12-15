/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:29:25 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/14 12:01:32 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACE_RAY_H
# define TRACE_RAY_H
# include "structs.h"

void	trace_rays(t_scene *s);

t_obj	*calculate_ray(t_scene *s, t_p c, t_p r, t_p *range);

#endif