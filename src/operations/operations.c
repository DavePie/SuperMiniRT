/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:41:46 by dvandenb          #+#    #+#             */
/*   Updated: 2024/01/08 15:39:27 by dvandenb         ###   ########.fr       */
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

int	set_if_zero(t_p v1, t_p v2, t_p p, float *a)
{
	int	found;

	found = 0;
	if (v1.x && !v2.x && ++found)
		*a = p.x / v1.x;
	if (v1.y && !v2.y && ++found)
		*a = p.y / v1.y;
	if (v1.z && !v2.z && ++found)
		*a = p.z / v1.z;
	return (found);
}

float	solve_one(t_p v1, t_p v2, float a, t_p p)
{
	if (v1.x && v2.x)
		return ((p.x - (a * v1.x)) / v2.x);
	if (v1.y && v2.y)
		return ((p.y - (a * v1.y)) / v2.y);
	return ((p.z - (a * v1.z)) / v2.z);
}

t_p	solve_vecs(t_p v1, t_p v2, t_p p)
{
	t_p	ans;
	int	found_a;
	int	found_b;

	found_a = set_if_zero(v1, v2, p, &ans.x);
	found_b = set_if_zero(v2, v1, p, &ans.y);
	if (found_a && found_b)
		return (ans);
	else if (found_a)
		ans.y = solve_one(v1, v2, ans.x, p);
	else
		ans.x = solve_one(v2, v1, ans.y, p);
	return (ans);
}
