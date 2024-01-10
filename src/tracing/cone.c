/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:10:39 by dvandenb          #+#    #+#             */
/*   Updated: 2024/01/10 14:12:33 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lighting.h"

void	co_norm(t_obj o, t_p p, t_p *n)
{
	t_p	v[4];

	sub(p, *o.p, &v[0]);
	eq(&v[1], v[0]);
	norm(&v[0]);
	cross(v[0], *norm(o.v), &v[2]);
	cross(v[0], v[2], n);
	norm(n);
	if (mag(v[1]) >= *o.h && fabs(acosf(dot(v[0], *o.v))
			- atanf(*o.w / *o.h / 2)) > 0.001)
		eq(n, *o.v);
}

void	co_img(t_obj o, t_img *i, t_p p, t_p *c)
{
	cy_img(o, i, p, c);
}

void	co_check(t_obj o, t_p p, t_p n, t_p *color)
{
	cy_check(o, p, n, color);
}

void	check_cone_cap(t_p p, t_p r, t_obj *cyl, t_p *ans)
{
	const t_p	cap_center_top = (t_p){.x = cyl->p->x + cyl->v->x * *cyl->h,
		.y = cyl->p->y + cyl->v->y * *cyl->h,
		.z = cyl->p->z + cyl->v->z * *cyl->h};
	const float	t_cap = intersect_plane(p, r, cap_center_top, *cyl->v);

	mult(r, t_cap, &r);
	add(p, r, &p);
	if (t_cap >= 0 && distance_squared(p,
			cap_center_top) <= (*cyl->w / 2) * (*cyl->w / 2))
		if (t_cap < ans->x)
			ans->x = t_cap;
}

// [theta, cos2(theta)]
// v -> r
// h -> norm(cone->vec)
// m -> (radius) ^2 / (height) ^ 2
// w -> p - cone->p
void	inter_ray_cone(t_p p, t_p r, t_obj *cone, t_p *ans)
{
	const float	m = (*cone->w * *cone->w / 4) / *cone->h / *cone->h;
	const t_p	w = (t_p){.x = p.x - cone->p->x, .y = p.y - cone->p->y,
		.z = p.z - cone->p->z};
	float		a[3];
	t_p			check;

	a[0] = dot(r, r) - ((m + 1) * powf(dot(r, *cone->v), 2));
	a[1] = 2 * (dot(r, w) - ((m + 1) * dot(r, *cone->v) * dot(w, *cone->v)));
	a[2] = a[1] * a[1] - (4 * a[0] * (dot(w, w) - ((m + 1)
					* powf(dot(w, *cone->v), 2))));
	ans->x = FLT_MAX;
	ans->y = FLT_MAX;
	ans->z = FLT_MAX;
	if (a[2] < 0)
		return ;
	ans->x = (-a[1] + sqrt(a[2])) / (2 * a[0]);
	sub(*add(*mult(r, ans->x, &check), p, &check), *cone->p, &check);
	if (dot(check, *cone->v) < 0 || dot(check, *cone->v) > *cone->h)
		ans->x = FLT_MAX;
	ans->y = (-a[1] - sqrt(a[2])) / (2 * a[0]);
	sub(*add(*mult(r, ans->y, &check), p, &check), *cone->p, &check);
	if (dot(check, *cone->v) < 0 || dot(check, *cone->v) > *cone->h)
		ans->y = FLT_MAX;
	if ((ans->x != FLT_MAX) || (ans->y != FLT_MAX))
		check_cone_cap(p, r, cone, ans);
}
