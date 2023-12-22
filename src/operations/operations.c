/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:41:46 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/22 23:58:32 by alde-oli         ###   ########.fr       */
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

t_p	*cross(t_p a, t_p b, t_p *ans)
{
	ans->x = a.y * b.z - (a.z * b.y);
	ans->y = a.z * b.x - (a.x * b.z);
	ans->z = a.x * b.y - (a.y * b.x);
	return (ans);
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

t_p	rotate_vector(t_p *v, t_p *axis, float angle)
{
	t_p			result;
	const float	cosa = cosf(angle);
	const float	sina = sinf(angle);

	result.x = axis->x * (axis->x * v->x + axis->y * v->y + axis->z * v->z)
		* (1 - cosa);
	result.y = axis->y * (axis->x * v->x + axis->y * v->y + axis->z * v->z)
		* (1 - cosa);
	result.z = axis->z * (axis->x * v->x + axis->y * v->y + axis->z * v->z)
		* (1 - cosa);
	result.x += v->x * cosa + (-axis->z * v->y + axis->y * v->z) * sina;
	result.y += v->y * cosa + (axis->z * v->x - axis->x * v->z) * sina;
	result.z += v->z * cosa + (-axis->y * v->x + axis->x * v->y) * sina;
	norm(&result);
	return (result);
}
