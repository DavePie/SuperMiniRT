/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:14:19 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/14 16:25:03 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "structs.h"

void	ft_error(int condition, char *mess, char *val, t_scene *s);

int		exit_scene(t_scene *s);

void	*ft_malloc(int size, t_scene *s);

t_obj	*add_back(t_obj **front, t_obj *obj);

t_obj	*new_obj(int type, t_scene *s);

t_p		*new_p(float x, float y, float z, t_scene *s);

float	mag(t_p a);

float	dot(t_p a, t_p b);

void	norm(t_p *a);

void	add(t_p *a, t_p b);

void	sub(t_p *a, t_p b);

void	mult(t_p *a, float b);

float	distance_squared(t_p a, t_p b);

#endif