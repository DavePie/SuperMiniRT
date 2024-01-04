/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:57:09 by dvandenb          #+#    #+#             */
/*   Updated: 2024/01/04 16:42:16 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_H
# define LIGHTING_H
# include "structs.h"
# include "minirt.h"

t_p		lighting(t_scene *s, t_obj o, t_p d, int depth);

void	sp_norm(t_obj o, t_p p, t_p *n);
void	sp_img(t_obj o, t_img *i, t_p p, t_p *c);
void	sp_check(t_obj o, t_p p, t_p *color);

void	pl_norm(t_obj o, t_p p, t_p *n);
void	pl_img(t_obj o, t_img *i, t_p p, t_p *c);
void	pl_check(t_obj o, t_p p, t_p *color);

void	cy_norm(t_obj o, t_p p, t_p *n);
void	cy_img(t_obj o, t_img *i, t_p p, t_p *c);
void	cy_check(t_obj o, t_p p, t_p *color);

void	co_norm(t_obj o, t_p p, t_p *n);
void	co_img(t_obj o, t_img *i, t_p p, t_p *c);
void	co_check(t_obj o, t_p p, t_p *color);


#endif