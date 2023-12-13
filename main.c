/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:07:57 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/13 18:31:19 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_mlx(t_scene *s)
{
	int	t;

	s->mlx = ft_malloc(sizeof(t_mlx), s);
	*s->mlx = (t_mlx){.mlx = mlx_init()};
	ft_error(!s->mlx->mlx, "failed to create window", 0, s);
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
	init_mlx(&scene);
	mlx_hook(scene.mlx->win, B_EXIT, 0, exit_scene, &scene);
	mlx_loop_hook(scene.mlx->mlx, update_window, &scene);
	
	t_obj *c = new_obj(0, &scene);
	c->p = new_p(0, 0, 0, &scene);
	add_back(&scene.camera, c);
	t_obj *s = new_obj(0, &scene);
	s->p = new_p(5, 5, 10, &scene);
	s->w = 3;
	s->color = 255 << 16;
	add_back(&scene.objects, s);
	
	t_obj *s2 = new_obj(0, &scene);
	s2->p = new_p(5, 5, 9, &scene);
	s2->w = 3;
	s2->color = 255 << 8;
	add_back(&scene.objects, s2);
	
	t_obj *s3 = new_obj(0, &scene);
	s3->p = new_p(2, 2, 9, &scene);
	s3->w = 3;
	s3->color = 255 << 8;
	add_back(&scene.objects, s3);
	
	t_obj *s4 = new_obj(0, &scene);
	s4->p = new_p(2, 3, 9, &scene);
	s4->w = 3;
	s4->color = 255 << 16;
	add_back(&scene.objects, s4);
	
	t_obj *s5 = new_obj(0, &scene);
	s5->w = 0.1;
	add_back(&scene.ambient, s5);
	
	t_obj *s6 = new_obj(0, &scene);
	s6->w = 0.6;
	s6->p = new_p (5,0,0,&scene);
	s6->v = new_p(0, 0, 1, &scene);
	add_back(&scene.lights, s6);

	trace_rays(&scene);
	mlx_loop(scene.mlx->mlx);
	return (0);
}
