/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:07:57 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/13 12:03:29 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_mlx(t_scene *s)
{
	s->mlx = ft_malloc(sizeof(t_mlx), s);
	*s->mlx = (t_mlx){.mlx = mlx_init()};
	ft_error(!s->mlx->mlx, "unable to create window", 0, s);
	s->mlx->win = mlx_new_window(s->mlx->mlx,
			INIT_WIDTH, INIT_HEIGHT, "SuperMiniRT");
	ft_error(!s->mlx->win, "unable to start windows", 0, s);
	s->mlx->width = INIT_WIDTH;
	s->mlx->height = INIT_HEIGHT;
	s->mlx->buffer = ft_malloc(sizeof(int) * INIT_WIDTH * INIT_HEIGHT, s);
	
}

int	main(int ac, char *av[])
{
	int		fd;
	t_scene	scene;

	scene = (t_scene){};
	ft_error(ac != 2, "invalid number of parameters", 0, &scene);
	fd = open(av[1], O_RDONLY);
	ft_error(fd == -1, "invalid file name: ", av[1], &scene);
	return (0);
}