/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:36:15 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/13 17:24:58 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minirt.h"

t_obj	*add_back(t_obj **front, t_obj *obj)
{
	t_obj	*cur;

	if (!*front)
	{
		*front = obj;
		return (obj);
	}
	cur = *front;
	while (cur->next)
		cur = cur->next;
	cur->next = obj;
	return (obj);
}

t_obj	*new_obj(int type, t_scene *s)
{
	t_obj	*temp;

	temp = ft_malloc(sizeof(t_obj), s);
	*temp = (t_obj){.type = type};
	return (temp);
}

t_p	*new_p(float x, float y, float z, t_scene *s)
{
	t_p	*temp;

	temp = ft_malloc(sizeof(t_p), s);
	*temp = (t_p){.x = x, .y = y, .z = z};
	return (temp);
}
