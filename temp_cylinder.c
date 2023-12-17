/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 12:53:46 by alde-oli          #+#    #+#             */
/*   Updated: 2023/12/16 12:53:46 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void inter_ray_cylinder(t_p p, t_p r, t_obj *cylinder, t_p *ans)
{
	const t_point	t = (t_point){.x = (-b + sqrt(discriminant)) / (2 * a), .y = (-b - sqrt(discriminant)) / (2 * a)}
	const t_point	co = (t_p){.x = p.x - cylinder->p->x, .y = p.y - cylinder->p->y, .z = p.z - cylinder->p->z};
	float 			a;
	float 			b;
	float 			c;

	a = dot(r, r) - pow(dot(r, v), 2);
	b = 2 * (dot(r, co) - dot(r, v) * dot(co, v));
	c = dot(co, co) - pow(dot(co, v), 2) - pow(cylinder->w / 2, 2);
	*ans = (t_p){.x = FLT_MAX, .y = FLT_MAX, .z = FLT_MAX};
	if (b * b - 4 * a * c < 0)
		return ;
	if (is_point_inside_cylinder_height(t.x, r, co, cylinder->v, cylinder->h))
		ans->x = t.x;
	if (is_point_inside_cylinder_height(t.y, r, co, cylinder->v, cylinder->h))
		ans->y = t.y;
	check_cylinder_caps(p, r, cylinder, ans, t0, t1);

	return;
}

int	is_point_inside_cylinder_height(float t, t_p r, t_p co, t_obj *cylinder)
{
	const t_p point = (t_p){.x = co.x + t * r.x, .y = co.y + t * r.y, .z = co.z + t * r.z};
	const float proj = dot(point, cylinder->v);

	return (proj >= 0 && proj <= cylinder->h);
}

void check_cylinder_caps(t_p p, t_p r, t_obj *cylinder, t_p *ans)
{
	const t_p	v = norm(*(cylinder->v));
	const t_p	cap_center_top = (t_p){.x = cylinder->p->x + v.x * cylinder->h, .y = cylinder->p->y + v.y * cylinder->h, .z = cylinder->p->z + v.z * cylinder->h};
	const t_p	t_cap = (t_p){.x = intersect_plane(p, r, *(cylinder->p), v), .y = intersect_plane(p, r, cap_center_top, v)};
	t_p 		p_copy;
	t_p 		r_copy;

	p_copy = (t_p){.x = p.x, .y = p.y, .z = p.z};
	r_copy = (t_p){.x = r.x, .y = r.y, .z = r.z};
	mult(&r_copy, t_cap.x);
	add(&p_copy, r_copy);
	if (t_cap.x >= 0 && distance_squared(p_copy, *(cylinder->p)) <= (cylinder->w / 2) * (cylinder->w / 2))
		update_ans_if_valid(t_cap.x, ans);
	mult(&r, t_cap.y);
	add(&p, r);
	if (t_cap.y >= 0 && distance_squared(p, cap_center_top) <= (cylinder->w / 2) * (cylinder->w / 2))
		update_ans_if_valid(t_cap.y, ans);
}

void update_ans_if_valid(float t, t_p *ans)
{
	if (t < ans->x)
	{
		ans->y = ans->x;
		ans->x = t;
	}
	else if (t < ans->y)
		ans->y = t;
}

float intersect_plane(t_p p, t_p r, t_p plane_point, t_p plane_normal)
{
	const float denom = dot(plane_normal, r);

	sub(plane_point, p);
	if (fabs(denom) > 1e-6)
		return (dot(plane_point, plane_normal) / denom);
	return (-1);
}
