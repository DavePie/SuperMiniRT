/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:41:46 by dvandenb          #+#    #+#             */
/*   Updated: 2024/01/08 18:00:23 by dvandenb         ###   ########.fr       */
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
