/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:09:39 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/15 14:10:48 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

void	free_objects(t_obj *o)
{
	t_obj	*cur;

	while (o)
	{
		cur = o;
		o = o->next;
		ft_free(cur->p);
		ft_free(cur->v);
		ft_free(cur);
	}
}

void	*ft_malloc(int size, t_scene *s)
{
	void	*temp;

	temp = malloc(size);
	ft_error(!temp, "unable to allocate space", 0, s);
	return (temp);
}

void	stop_threads(t_scene *s)
{
	int	i;

	i = -1;
	if (s->multi_t)
	{
		*s->multi_t->do_exit = 1;
		i = -1;
		while (++i < NUM_THREADS)
			pthread_join(s->multi_t->pids[i], NULL);
	}
}

int	exit_scene(t_scene *s)
{
	if (!s)
		exit(s->exit_code);
	stop_threads(s);
	free_objects(s->ambient);
	free_objects(s->camera);
	free_objects(s->lights);
	free_objects(s->objects);
	if (!s->mlx)
		exit(s->exit_code);
	if (s->mlx->img)
		mlx_destroy_image(s->mlx->mlx, s->mlx->img);
	ft_free(s->mlx->buffer);
	if (s->mlx->mlx && s->mlx->win)
		mlx_destroy_window(s->mlx->mlx, s->mlx->win);
	free(s->mlx);
	exit(s->exit_code);
	return (1);
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
