/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:41:46 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/17 23:00:04 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minirt.h"

float	mag(t_p a)
{
	return (sqrtf(a.x * a.x + a.y * a.y + a.z * a.z));
}

float	dot(t_p a, t_p b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

void	cross(t_p a, t_p b, t_p *ans)
{
	ans->x = a.y * b.z - (a.z * b.y);
	ans->y = a.z * b.x - (a.x * b.z);
	ans->z = a.x * b.y - (a.y * b.x);
}

void	add(t_p *a, t_p b)
{
	a->x = a->x + b.x;
	a->y = a->y + b.y;
	a->z = a->z + b.z;
}

void	sub(t_p *a, t_p b)
{
	a->x = a->x - b.x;
	a->y = a->y - b.y;
	a->z = a->z - b.z;
}

void	mult(t_p *a, float b)
{
	a->x = a->x * b;
	a->y = a->y * b;
	a->z = a->z * b;
}

void	norm(t_p *a)
{
	float	magi;

	magi = mag(*a);
	if (!magi)
		return ;
	a->x /= magi;
	a->y /= magi;
	a->z /= magi;
}

float	distance_squared(t_p a, t_p b)
{
	return (powf(a.x - b.x, 2) + powf(a.y - b.y, 2) + powf(a.z - b.z, 2));
}
