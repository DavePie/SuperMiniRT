/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersec_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 12:53:46 by alde-oli          #+#    #+#             */
/*   Updated: 2023/12/17 18:29:59 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "structs.h"

static int		is_point_inside_cyl_height(float t, t_p r, t_p co, t_obj *cyl);
static void		check_cylinder_caps(t_p p, t_p r, t_obj *cyl, t_p *ans);
static float	intersect_plane(t_p p, t_p r, t_p plane_p, t_p plane_normal);

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
	const float	c = dot(co, co) - pow(dot(co, *cyl->v), 2) - pow(cyl->w / 2, 2);
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

	return (proj >= 0 && proj <= cyl->h);
}

//cap_center_top is cyl->p at the top
//t_cap.x is distance from ray origin to intersection point with bottom cap
//t_cap.y is distance from  ray origin tothe intersection point with top cap
static void	check_cylinder_caps(t_p p, t_p r, t_obj *cyl, t_p *ans)
{
	const t_p	cap_center_top = (t_p){.x = cyl->p->x + cyl->v->x * cyl->h,
		.y = cyl->p->y + cyl->v->y * cyl->h,
		.z = cyl->p->z + cyl->v->z * cyl->h};
	const t_p	t_cap = (t_p){.x = intersect_plane(p, r, *(cyl->p), *cyl->v),
		.y = intersect_plane(p, r, cap_center_top, *cyl->v)};
	t_p			p_copy;
	t_p			r_copy;

	p_copy = (t_p){.x = p.x, .y = p.y, .z = p.z};
	r_copy = (t_p){.x = r.x, .y = r.y, .z = r.z};
	mult(&r_copy, t_cap.x);
	add(&p_copy, r_copy);
	if (t_cap.x >= 0 && distance_squared(p_copy,
			*(cyl->p)) <= (cyl->w / 2) * (cyl->w / 2))
		if (t_cap.x < ans->x)
			ans->x = t_cap.x;
	mult(&r, t_cap.y);
	add(&p, r);
	if (t_cap.y >= 0 && distance_squared(p,
			cap_center_top) <= (cyl->w / 2) * (cyl->w / 2))
		if (t_cap.y < ans->x)
			ans->x = t_cap.y;
}

static float	intersect_plane(t_p p, t_p r, t_p plane_p, t_p plane_normal)
{
	const float	denom = dot(plane_normal, r);

	sub(&plane_p, p);
	if (fabs(denom) > 1e-6)
		return (dot(plane_p, plane_normal) / denom);
	return (-1);
}
