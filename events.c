/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:21:28 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/20 14:37:55 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int	update_window(t_scene *s)
{
	mlx_put_image_to_window(s->mlx->mlx, s->mlx->win, s->mlx->img, 0, 0);
	return (0);
}

int	key_event(int key, t_scene *s)
{
	t_p			temp;
	t_p			temp2;
	const float	rot = 0.05;
	t_p			*cv;

	cv = s->camera->v;
	if (key == K_ESC)
		exit_scene(s);
	if (key == K_W)
	{
		add(*s->camera->p, *s->camera->v, s->camera->p);
		stop_threads(s);
		trace_rays(s);
	}
	if (key == K_A)
	{
		temp2 = (t_p){.x = 0, .y = 1, .z = 0};
		cross(*s->camera->v, temp2, &temp);
		add(*s->camera->p, temp, s->camera->p);
		stop_threads(s);
		trace_rays(s);
	}
	if (key == K_D)
	{
		temp2 = (t_p){.x = 0, .y = -1, .z = 0};
		cross(*s->camera->v, temp2, &temp);
		add(*s->camera->p, temp, s->camera->p);
		stop_threads(s);
		trace_rays(s);
	}
	if (key == K_S)
	{
		sub(*s->camera->p, *s->camera->v, s->camera->p);
		stop_threads(s);
		trace_rays(s);
	}
	if (key == K_LEFT)
	{
		temp = (t_p){.x = cosf(rot) * cv->x - (sinf(rot) * cv->z),
			.z = sinf(rot) * cv->x + (cosf(rot) * cv->z), .y = cv->y};
		norm(&temp);
		*cv = temp;
		stop_threads(s);
		trace_rays(s);
	}
	if (key == K_RIGHT)
	{
		temp = (t_p){.x = cosf(-rot) * cv->x - (sinf(-rot) * cv->z),
			.z = sinf(-rot) * cv->x + (cosf(-rot) * cv->z), .y = cv->y};
		norm(&temp);
		*cv = temp;
		stop_threads(s);
		trace_rays(s);
	}
	if (key == K_DOWN)
	{
		temp = (t_p){.x = cosf(-rot) * cv->x - (sinf(-rot) * cv->y),
			.y = sinf(-rot) * cv->x + (cosf(-rot) * cv->y), .z = cv->z};
		norm(&temp);
		*cv = temp;
		stop_threads(s);
		trace_rays(s);
	}
	if (key == K_UP)
	{
		temp = (t_p){.x = cosf(rot) * cv->x - (sinf(rot) * cv->y),
			.y = sinf(rot) * cv->x + (cosf(rot) * cv->y), .z = cv->z};
		norm(&temp);
		*cv = temp;
		stop_threads(s);
		trace_rays(s);
	}
	return (0);
}
