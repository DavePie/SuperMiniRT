/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:41:46 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/20 14:38:32 by dvandenb         ###   ########.fr       */
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

t_p	*add(t_p a, t_p b, t_p *ans)
{
	ans->x = a.x + b.x;
	ans->y = a.y + b.y;
	ans->z = a.z + b.z;
	return (ans);
}

t_p	*sub(t_p a, t_p b, t_p *ans)
{
	ans->x = a.x - b.x;
	ans->y = a.y - b.y;
	ans->z = a.z - b.z;
	return (ans);
}

t_p	*mult(t_p a, float b, t_p *ans)
{
	ans->x = a.x * b;
	ans->y = a.y * b;
	ans->z = a.z * b;
	return (ans);
}

t_p	*eq(t_p *a, t_p b)
{
	a->x = b.x;
	a->y = b.y;
	a->z = b.z;
	return (a);
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
