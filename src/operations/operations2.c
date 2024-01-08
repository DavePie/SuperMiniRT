/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:53:48 by dvandenb          #+#    #+#             */
/*   Updated: 2024/01/08 17:54:10 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minirt.h"

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

t_p	*norm(t_p *a)
{
	float	magi;

	magi = mag(*a);
	if (!magi)
		return (0);
	a->x /= magi;
	a->y /= magi;
	a->z /= magi;
	return (a);
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
	const float	dot_p = dot(*axis, *v);

	mult(*axis, (dot_p) * (1 - cosa), &result);
	result.x += v->x * cosa + (axis->y * v->z - axis->z * v->y) * sina;
	result.y += v->y * cosa + (axis->z * v->x - axis->x * v->z) * sina;
	result.z += v->z * cosa + (axis->x * v->y - axis->y * v->x) * sina;
	norm(&result);
	return (result);
}
