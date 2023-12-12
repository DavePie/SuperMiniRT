/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:47:35 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/12 12:47:49 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_p
{
	float x;
	float y;
	float z;
} t_p;

typedef struct s_obj
{
	int type;
	unsigned int color;
	t_obj *next;
	t_p p;
	t_p v;
	float w;
	float h;
}	t_obj;

typedef struct s_scene
{
	t_obj *ambient;
	t_obj *camera;
	t_obj *lights;
	t_obj *objects;
} t_scene;