/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:09:39 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/12 17:12:41 by dvandenb         ###   ########.fr       */
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

void	free_mlx(t_mlx *m)
{
	if (!m)
		return ;
	if (m->mlx && m->win)
		mlx_destroy_window(m->mlx, m->win);
	free(m);
}

void	free_scene(t_scene *s)
{
	if (!s)
		return ;
	free_objects(s->ambient);
	free_objects(s->camera);
	free_objects(s->lights);
	free_objects(s->objects);
	free_mlx(s->mlx);
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
		free_scene(s);
		exit(1);
	}
}
