/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:07:57 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/21 11:43:13 by alde-oli         ###   ########.fr       */
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


int r(int input)
{
	return (rand()) / (RAND_MAX / input);
}

int	main(int ac, char *av[])
{
	int		fd;
	t_scene	scene;

	scene = (t_scene){};
	ft_error(ac != 2, "invalid number of parameters", 0, &scene);
	fd = open(av[1], O_RDONLY);
	ft_error(fd == -1, "invalid file name: ", av[1], &scene);
	get_objs(&scene, fd);
	init_mlx(&scene);
	mlx_hook(scene.mlx->win, B_EXIT, 0, exit_scene, &scene);
	if (LINUX)
		mlx_hook(scene.mlx->win, 2, 1L << 0, key_l_event, &scene);
	else
		mlx_key_hook(scene.mlx->win, key_event, &scene);
	mlx_loop_hook(scene.mlx->mlx, update_window, &scene);

	// t_obj *c = new_obj(0, &scene);
    // c->p = new_p(-20, -20, -50, &scene);
    // c->v = new_p(1, 1, 2, &scene);
    // norm(c->v);
    // add_back(&scene.camera, c);

    // t_obj *s5 = new_obj(0, &scene);
    // s5->w = 0.2;
    // add_back(&scene.ambient, s5);

    t_obj *s6 = new_obj(0, &scene);
    s6->w = 0.4;
    s6->p = new_p (50, 0, -50, &scene);
    add_back(&scene.lights, s6);

    // t_obj *s7 = new_obj(0, &scene);
    // s7->w = 0.4;
    // s7->p = new_p (10, -40, 0, &scene);
    // add_back(&scene.lights, s7);

    // t_obj *cyl = new_obj(2, &scene);
    // cyl->p = new_p(8, 0, 0, &scene);
	// cyl->v = new_p(0, 1, 0, &scene);
    // cyl->w = 5;
	// cyl->h = 8;
    // cyl->color = cl(255, 0, 0);
    // add_back(&scene.objects, cyl);

    // t_obj *plane = new_obj(1, &scene);
    // plane->p = new_p(0, 0, 30, &scene);
    // plane->v = new_p(0, 0, -1, &scene);
    // norm(plane->v);
    // plane->color = cl(255, 255, 255);
    // plane->reflect = 1;
    // add_back(&scene.objects, plane);


	// for (int i = 0; i < 50; i++)
	// {
	// 	t_obj *temp = new_obj(2, &scene);
	// 	temp->w = (float)(r(10) + 1)/5;
	// 	temp->h = (float)(r(10) + 1)/5;
	// 	printf("w: %f\n", temp->w);
	// 	temp->p = new_p((float)(r(40) - 20) / 2, (float)(r(40) - 20) / 2, 13 + (float)(r(40) - 20) / 2, &scene);
	// 	temp->v = new_p((float)(r(40) - 20) / 2, (float)(r(40) - 20) / 2, 13 + (float)(r(40) - 20) / 2, &scene);
	// 	norm(temp->v);
	// 	temp->color = cl(r(255), r(255), r(255));
	// 	add_back(&scene.objects, temp);
	// }
	
	// for (int i = 0; i < 800; i++)
	// {
	// 	t_obj *temp = new_obj(0, &scene);
	// 	temp->w = (float)(r(10) + 1)/5;
	// 	printf("w: %f\n", temp->w);
	// 	temp->p = new_p((float)(r(40) - 20) / 2, (float)(r(40) - 20) / 2, 13 + (float)(r(40) - 20) / 2, &scene);
	// 	temp->color = cl(r(255), r(255), r(255));
	// 	add_back(&scene.objects, temp);
	// }

	trace_rays(&scene);
	mlx_loop(scene.mlx->mlx);
	return (0);
}
