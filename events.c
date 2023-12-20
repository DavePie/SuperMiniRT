/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:21:28 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/20 23:27:10 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int	update_window(t_scene *s)
{
	mlx_put_image_to_window(s->mlx->mlx, s->mlx->win, s->mlx->img, 0, 0);
	return (0);
}

void	change_pos(t_p *pos, t_p dir, t_p *orient, t_scene *s)
{
	const t_p	up = {0, 1, 0};
	t_p			right;

	cross(*orient, up, &right);
	pos->x += dir.x * orient->x;
	pos->y += dir.x * orient->y;
	pos->z += dir.x * orient->z;
	pos->x += dir.y * right.x;
	pos->y += dir.y * right.y;
	pos->z += dir.y * right.z;
	pos->y += dir.z;
	stop_threads(s);
	trace_rays(s);
}


void	change_angle(t_p *v, int dir, t_scene *s)
{
	t_p	temp;

	if (dir == RJ_UP)
		temp = (t_p){.x = cosf(0.05) * v->x - (sinf(0.05) * v->y),
			.y = sinf(0.05) * v->x + (cosf(0.05) * v->y), .z = v->z};
	if (dir == RJ_DOWN)
		temp = (t_p){.x = cosf(-0.05) * v->x - (sinf(-0.05) * v->y),
			.y = sinf(-0.05) * v->x + (cosf(-0.05) * v->y), .z = v->z};
	if (dir == RJ_LEFT)
		temp = (t_p){.x = cosf(0.05) * v->x - (sinf(0.05) * v->z),
			.z = sinf(0.05) * v->x + (cosf(0.05) * v->z), .y = v->y};

	if (dir == RJ_RIGHT)
		temp = (t_p){.x = cosf(-0.05) * v->x - (sinf(-0.05) * v->z),
			.z = sinf(-0.05) * v->x + (cosf(-0.05) * v->z), .y = v->y};
	norm(&temp);
	*v = temp;
	stop_threads(s);
	trace_rays(s);
}

//for linux
int	key_l_event(int key, t_scene *s)
{
	if (key == K_ESC)
		exit_scene(s);
	if (key == LJ_UP)
		change_pos(s->camera->p, (t_p){.x = 1}, s->camera->v, s);
	if (key == LJ_DOWN)
		change_pos(s->camera->p, (t_p){.x = -1}, s->camera->v, s);
	if (key == LJ_LEFT)
		change_pos(s->camera->p, (t_p){.y = 1}, s->camera->v, s);
	if (key == LJ_RIGHT)
		change_pos(s->camera->p, (t_p){.y = -1}, s->camera->v, s);
	if (key == LS)
		change_pos(s->camera->p, (t_p){.z = 1}, s->camera->v, s);
	if (key == RS)
		change_pos(s->camera->p, (t_p){.z = -1}, s->camera->v, s);
	if (key == RJ_UP)
		change_angle(s->camera->v, RJ_UP, s);
	if (key == RJ_DOWN)
		change_angle(s->camera->v, RJ_DOWN, s);
	if (key == RJ_LEFT)
		change_angle(s->camera->v, RJ_LEFT, s);
	if (key == RJ_RIGHT)
		change_angle(s->camera->v, RJ_RIGHT, s);
	return (0);
}

int	key_event(int key, t_scene *s)
{
	if (LINUX)
		return (key_l_event(key, s));
	if (key == K_ESC)
		exit_scene(s);
	if (key == K_W)
		change_pos(s->camera->p, (t_p){.x = 1}, s->camera->v, s);
	if (key == K_A)
		change_pos(s->camera->p, (t_p){.y = 1}, s->camera->v, s);
	if (key == K_D)
		change_pos(s->camera->p, (t_p){.y = -1}, s->camera->v, s);
	if (key == K_S)
		change_pos(s->camera->p, (t_p){.x = -1}, s->camera->v, s);
	if (key == K_LEFT)
		change_angle(s->camera->v, RJ_LEFT, s);
	if (key == K_RIGHT)
		change_angle(s->camera->v, RJ_RIGHT, s);
	if (key == K_DOWN)
		change_angle(s->camera->v, RJ_DOWN, s);
	if (key == K_UP)
		change_angle(s->camera->v, RJ_UP, s);
	return (0);
}
