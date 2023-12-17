/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:21:28 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/15 14:46:33 by dvandenb         ###   ########.fr       */
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
	if (key == K_ESC)
		exit_scene(s);
	return (0);
}
