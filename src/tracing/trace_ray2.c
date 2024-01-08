/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 12:53:46 by alde-oli          #+#    #+#             */
/*   Updated: 2024/01/08 18:46:25 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "structs.h"
#include "utils.h"

static int		is_point_inside_cyl_height(float t, t_p r, t_p co, t_obj *cyl);
float			intersect_plane(t_p p, t_p r, t_p plane_p, t_p plane_normal);
typedef void	(*t_INTER)(t_p, t_p, t_obj *, t_p *);

int	calculate_shadow(t_scene *s, t_p p, t_p r, t_p *range)
{
	float			min_l;
	t_obj			*cur;
	t_p				t;
	const t_INTER	intersect[4] = {&inter_ray_sphere, &inter_ray_plane,
		&inter_ray_cylinder, &inter_ray_cone};

	min_l = FLT_MAX;
	cur = s->objects;
	while (cur)
	{
		intersect[*(cur->type)](p, r, cur, &t);
		if ((t.x >= range->x && t.x <= range->y && t.x < min_l)
			|| (t.y >= range->x && t.y <= range->y && t.y < min_l))
			return (1);
		cur = cur->next;
	}
	range->z = min_l;
	return (0);
}

//a,b,c are the coefficients of the quadratic equation
//co is the distance from the ray origin to the intersection point
//t.x and t.y are the two solutions of the quadratic equation
//ans is the answer, it is updated if the intersection point is valid
void	inter_ray_cylinder(t_p p, t_p r, t_obj *cyl, t_p *ans)
{
	const t_p	co = (t_p){.x = p.x - cyl->p->x,
		.y = p.y - cyl->p->y, .z = p.z - cyl->p->z};
	const float	a = dot(r, r) - pow(dot(r, *cyl->v), 2);
	const float	b = 2 * (dot(r, co) - dot(r, *cyl->v) * dot(co, *cyl->v));
	const float	c = dot(co, co) - pow(dot(co, *cyl->v), 2)
		- pow(*cyl->w / 2, 2);
	const t_p	t = (t_p){.x = (-b + sqrt(b * b - 4 * a * c)) / (2 * a),
		.y = (-b - sqrt(b * b - 4 * a * c)) / (2 * a)};

	*ans = (t_p){.x = FLT_MAX, .y = FLT_MAX, .z = FLT_MAX};
	if (b * b - 4 * a * c < 0)
		return ;
	if (is_point_inside_cyl_height(t.x, r, co, cyl))
		ans->x = t.x;
	if (is_point_inside_cyl_height(t.y, r, co, cyl))
		ans->y = t.y;
	if (ans->y < ans->x)
		ans->x = ans->y;
	ans->y = FLT_MAX;
	check_cylinder_caps(p, r, cyl, ans);
	return ;
}

static int	is_point_inside_cyl_height(float t, t_p r, t_p co, t_obj *cyl)
{
	const t_p	point = (t_p){.x = co.x + t * r.x,
		.y = co.y + t * r.y, .z = co.z + t * r.z};
	const float	proj = dot(point, *cyl->v);

	return (proj >= 0 && proj <= *cyl->h);
}

//cap_center_top is cyl->p at the top
//t_cap.x is distance from ray origin to intersection point with bottom cap
//t_cap.y is distance from  ray origin tothe intersection point with top cap
void	check_cylinder_caps(t_p p, t_p r, t_obj *cyl, t_p *ans)
{
	const t_p	cap_center_top = (t_p){.x = cyl->p->x + cyl->v->x * *cyl->h,
		.y = cyl->p->y + cyl->v->y * *cyl->h,
		.z = cyl->p->z + cyl->v->z * *cyl->h};
	const t_p	t_cap = (t_p){.x = intersect_plane(p, r, *(cyl->p), *cyl->v),
		.y = intersect_plane(p, r, cap_center_top, *cyl->v)};
	t_p			p_copy;
	t_p			r_copy;

	p_copy = (t_p){.x = p.x, .y = p.y, .z = p.z};
	r_copy = (t_p){.x = r.x, .y = r.y, .z = r.z};
	mult(r_copy, t_cap.x, &r_copy);
	add(p_copy, r_copy, &p_copy);
	if (t_cap.x >= 0 && distance_squared(p_copy,
			*(cyl->p)) <= (*cyl->w / 2) * (*cyl->w / 2))
		if (t_cap.x < ans->x)
			ans->x = t_cap.x;
	mult(r, t_cap.y, &r);
	add(p, r, &p);
	if (t_cap.y >= 0 && distance_squared(p,
			cap_center_top) <= (*cyl->w / 2) * (*cyl->w / 2))
		if (t_cap.y < ans->x)
			ans->x = t_cap.y;
}

float	intersect_plane(t_p p, t_p r, t_p plane_p, t_p plane_normal)
{
	const float	denom = dot(plane_normal, r);

	sub(plane_p, p, &plane_p);
	if (fabs(denom) > 1e-6)
		return (dot(plane_p, plane_normal) / denom);
	return (-1);
}
