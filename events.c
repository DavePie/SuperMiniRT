/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:21:28 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/14 17:52:38 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int	update_window(t_scene *s)
{
	// for (int i = 0; i < s->mlx->width; i++)
	// {
	// 	for (int j = 0; j < s->mlx->height; j++)
	// 	{
	// 		put_pixel(s, i, j, 255 << 16);
	// 	}
	// }
	mlx_put_image_to_window(s->mlx->mlx, s->mlx->win, s->mlx->img, 0, 0);
	return (0);
}

int	key_event(int key, t_scene *s)
{
	if (key == K_ESC)
		exit_scene(s);
	return (0);
}
