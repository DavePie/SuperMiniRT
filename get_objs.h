/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 12:55:10 by alde-oli          #+#    #+#             */
/*   Updated: 2023/12/21 18:28:37 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_OBJS_H
# define GET_OBJS_H

# include "minirt.h"

int		count_words(char *line);
int		do_split(char *line, char ***split, const int *atr);
void	*get_color(char *line, t_scene *s);
void	*get_coords(char *line, t_scene *scene);
int		match_t(char *line, int *i, t_obj *new_obj);
float	ft_atof(char *str);
void	set_attributes(t_obj *new_obj, char *line, int fd,
			t_scene *scene);
int		get_one_obj(t_scene *scene, int fd, char *line, t_obj *new_obj);
void	get_objs(t_scene *scene, int fd);

#endif