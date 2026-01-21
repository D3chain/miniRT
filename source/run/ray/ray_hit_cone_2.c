/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit_cone_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 10:46:36 by echatela          #+#    #+#             */
/*   Updated: 2026/01/21 14:29:10 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

__attribute__((always_inline, hot))
t_hit_info
	create_hit(t_real dst, const t_ray *ray, const t_cone *co, t_real3 normal)
{
	t_hit_info	hit;

	hit.did_hit = true;
	hit.dst = dst;
	hit.hit_point = project(ray->origin, ray->dir, dst);
	hit.normal = normal;
	hit.material = co->material;
	return (hit);
}

__attribute__((always_inline, hot))
static bool	is_within_cone_height(const t_cone *cone, t_real3 point)
{
	t_real3	apex_to_point;
	t_real	projection;

	apex_to_point = minus3(point, cone->apex);
	projection = dot(apex_to_point, cone->axis);
	return (projection >= EPSILON && projection <= cone->height);
}

__attribute__((always_inline, hot))
static t_real3	compute_cone_normal(const t_cone *cone, t_real3 point)
{
	t_real3	apex_to_point;
	t_real	projection;
	t_real3	axis_point;

	apex_to_point = minus3(point, cone->apex);
	projection = dot(apex_to_point, cone->axis);
	axis_point = project(cone->apex, cone->axis, projection);
	return (normalize3(minus3(point, axis_point)));
}

__attribute__((always_inline, hot))
inline t_hit_info	intersect_cone_cap(const t_ray *ray, const t_cone *cone)
{
	t_real		denom;
	t_real		t;
	t_real3		point;
	t_real3		base_to_point;

	denom = dot(ray->dir, cone->axis);
	if (fabs(denom) < EPSILON)
		return ((t_hit_info){0});
	t = dot(minus3(cone->base, ray->origin), cone->axis) / denom;
	if (t <= EPSILON)
		return ((t_hit_info){0});
	point = project(ray->origin, ray->dir, t);
	base_to_point = minus3(point, cone->base);
	if (dot(base_to_point, base_to_point) <= cone->radius_sq)
		return (create_hit(t, ray, cone, cone->axis));
	return ((t_hit_info){0});
}

__attribute__((always_inline, hot))
inline t_hit_info	intersect_cone_body(const t_ray *ray, const t_cone *cone)
{
	t_real3		x;
	t_real		coefs[3];
	t_real		t[2];
	t_real3		point;

	x = minus3(ray->origin, cone->apex);
	compute_cone_quadratic(cone, ray, x, coefs);
	if (!solve_quadratic(coefs, &t[0], &t[1]))
		return ((t_hit_info){0});
	if (t[0] > EPSILON)
	{
		point = project(ray->origin, ray->dir, t[0]);
		if (is_within_cone_height(cone, point))
			return (create_hit(t[0], ray, cone, \
				compute_cone_normal(cone, point)));
	}
	if (t[1] > EPSILON)
	{
		point = project(ray->origin, ray->dir, t[1]);
		if (is_within_cone_height(cone, point))
			return (create_hit(t[1], \
				ray, cone, compute_cone_normal(cone, point)));
	}
	return ((t_hit_info){0});
}
