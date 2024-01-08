/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_vecs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:54:34 by dvandenb          #+#    #+#             */
/*   Updated: 2024/01/08 17:54:44 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minirt.h"

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
