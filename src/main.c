/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:07:57 by dvandenb          #+#    #+#             */
/*   Updated: 2024/01/08 18:27:19 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include "get_next_line.h"

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

void	get_objs(t_scene *scene, int fd)
{
	t_obj	*new_obj;
	char	*line;

	while (1)
	{
		new_obj = ft_malloc(sizeof(t_obj), scene);
		*new_obj = (t_obj){};
		line = get_next_line(fd);
		if (!line || *line == '\0')
		{
			free(new_obj);
			if (line)
				free(line);
			break ;
		}
		if (*line == '\n')
		{
			free(line);
			free(new_obj);
		}
		else
			get_one_obj(scene, fd, line, new_obj);
	}
	if (!scene->camera || !scene->ambient || !scene->lights)
		ft_error(1, "Missing scene element\n", 0, scene);
}

void	ft_error(int condition, char *mess, char *val, t_scene *s)
{
	if (condition)
	{
		write(2, "error: ", 7);
		while (*mess)
			write(2, mess++, 1);
		while (val && *val)
			write(2, val++, 1);
		write(2, "\n", 1);
		s->exit_code = 1;
		exit_scene(s);
	}
}

int	main(int ac, char *av[])
{
	int		fd;
	t_scene	scene;

	scene = (t_scene){};
	ft_error(ac != 2, "invalid number of parameters", 0, &scene);
	fd = 1;
	ft_error((ft_strlen(av[1]) < 4 || ft_strncmp(av[1] + ft_strlen(av[1]) - 3,
				".rt", 3)), "invalid file extension: ", av[1], &scene);
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
