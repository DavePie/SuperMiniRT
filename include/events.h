/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:23:00 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/20 22:17:10 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H
# include "minirt.h"
# include "structs.h"

int	update_window(t_scene *s);

int	key_l_event(int key, t_scene *s);

int	key_event(int key, t_scene *s);

#endif