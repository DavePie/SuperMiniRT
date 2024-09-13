/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:21:28 by dvandenb          #+#    #+#             */
/*   Updated: 2024/01/10 10:56:58 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "minirt.h"

int	update_window(t_scene *s)
{
	mlx_put_image_to_window(s->mlx->mlx, s->mlx->win, s->mlx->img, 0, 0);
	return (0);
}

void	change_pos(t_p *pos, int key, t_p *orient, t_scene *s)
{
	const t_p	up = {0, 1, 0};
	t_p			right;
	const t_p	dir[6] = {{.x = 1}, {.x = -1}, {.y = 1},
	{.y = -1}, {.z = 1}, {.z = -1}};
	const int	i = (0 * (key == LJ_UP || key == K_W))
		+ (1 * (key == LJ_DOWN || key == K_S))
		+ (2 * (key == LJ_LEFT || key == K_A))
		+ (3 * (key == LJ_RIGHT || key == K_D))
		+ (4 * (key == LS))
		+ (5 * (key == RS));

	cross(*orient, up, &right);
	pos->x += dir[i].x * orient->x + dir[i].y * right.x;
	pos->y += dir[i].x * orient->y + dir[i].y * right.y;
	pos->z += dir[i].x * orient->z + dir[i].y * right.z;
	pos->x += dir[i].y * right.x;
	pos->y += dir[i].y * right.y;
	pos->z += dir[i].y * right.z;
	pos->y += dir[i].z;
	stop_threads(s);
	trace_rays(s);
}

void	change_angle(t_p *v, int dir, t_scene *s)
{
	const float	angle_increment = 2 * M_PI / 180.0;
	t_p			right;
	t_p			temp;

	cross(*v, (t_p){0, 1, 0}, &right);
	if (dir == RJ_UP || dir == K_UP)
		temp = rotate_vector(v, &right, -angle_increment);
	else if (dir == RJ_DOWN || dir == K_DOWN)
		temp = rotate_vector(v, &right, angle_increment);
	else if (dir == RJ_LEFT || dir == K_LEFT)
		temp = rotate_vector(v, &(t_p){0, 1, 0}, -angle_increment);
	else if (dir == RJ_RIGHT || dir == K_RIGHT)
		temp = rotate_vector(v, &(t_p){0, 1, 0}, angle_increment);
	if (fabs(temp.y) < 1)
		*v = temp;
	stop_threads(s);
	trace_rays(s);
}

//for linux
int	key_l_event(int key, t_scene *s)
{
	if (key == K_ESC)
		exit_scene(s);
	if (key == LJ_UP || key == LJ_DOWN || key == LJ_LEFT || key == LJ_RIGHT
		|| key == LS || key == RS)
		change_pos(s->camera->p, key, s->camera->v, s);
	if (key == RJ_UP || key == RJ_DOWN || key == RJ_LEFT || key == RJ_RIGHT)
		change_angle(s->camera->v, key, s);
	return (0);
}

int	key_event(int key, t_scene *s)
{
	if (CONTROLLER)
		return (key_l_event(key, s));
	if (key == K_ESC)
		exit_scene(s);
	if (key == K_W || key == K_A || key == K_D || key == K_S || key == LS
		|| key == RS)
		change_pos(s->camera->p, key, s->camera->v, s);
	if (key == K_LEFT || key == K_RIGHT || key == K_UP || key == K_DOWN)
		change_angle(s->camera->v, key, s);
	return (0);
}
