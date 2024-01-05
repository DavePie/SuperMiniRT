/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:07:57 by dvandenb          #+#    #+#             */
/*   Updated: 2024/01/05 15:42:39 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_mlx(t_scene *s)
{
	int	t;

	s->mlx->win = mlx_new_window(s->mlx->mlx,
			INIT_WIDTH, INIT_HEIGHT, "SuperMiniRT");
	ft_error(!s->mlx->win, "failed to start windows", 0, s);
	s->mlx->width = INIT_WIDTH;
	s->mlx->height = INIT_HEIGHT;
	s->mlx->buffer = ft_malloc(sizeof(int) * INIT_WIDTH * INIT_HEIGHT, s);
	s->mlx->img = mlx_new_image(s->mlx->mlx, INIT_WIDTH, INIT_HEIGHT);
	ft_error(!s->mlx->img, "failed to create image", 0, s);
	s->mlx->pix = mlx_get_data_addr(s->mlx->img, &t, &t, &t);
}

int	main(int ac, char *av[])
{
	int		fd;
	t_scene	scene;

	scene = (t_scene){};
	ft_error(ac != 2, "invalid number of parameters", 0, &scene);
	fd = open(av[1], O_RDONLY);
	ft_error(fd == -1, "invalid file name: ", av[1], &scene);
	scene.mlx = ft_malloc(sizeof(t_mlx), &scene);
	*scene.mlx = (t_mlx){.mlx = mlx_init()};
	ft_error(!scene.mlx->mlx, "failed to create window", 0, &scene);
	get_objs(&scene, fd);
	init_mlx(&scene);
	mlx_hook(scene.mlx->win, B_EXIT, 0, exit_scene, &scene);
	mlx_hook(scene.mlx->win, 2, 1L << 0, key_event, &scene);
	mlx_loop_hook(scene.mlx->mlx, update_window, &scene);
	trace_rays(&scene);
	mlx_loop(scene.mlx->mlx);
	return (0);
}
