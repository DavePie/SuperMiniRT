/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:41:46 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/13 17:24:46 by dvandenb         ###   ########.fr       */
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
