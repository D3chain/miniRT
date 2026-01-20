/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit_cylinder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:55:56 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/20 20:28:02 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

__attribute__((hot))
static t_sol2	caps_intersect(const struct s_ray *ray, \
	const struct s_cylinder *cylinder)
{
	t_sol2			sol;
	const t_real3	p1 = project(cylinder->coord, cylinder->axis, \
		cylinder->height / FLT_2);
	const t_real3	p2 = project(cylinder->coord, \
		fmul3(cylinder->axis, -FLT_1), cylinder->height / FLT_2);
	const t_real	rdot = dot(cylinder->axis, ray->dir);

	if (ft_dblcmp(rdot, FLT_0, EPSILON) == FLT_0)
		return (sol.n = 0, sol);
	sol.n = 2;
	sol.r1 = plane_dst(ray, cylinder->axis, p1);
	if (sqdot(minus3(project(ray->origin, ray->dir, sol.r1), p1))
		> cylinder->radius_sq)
		sol.r1 = -FLT_1;
	sol.r2 = plane_dst(ray, cylinder->axis, p2);
	if (sqdot(minus3(project(ray->origin, ray->dir, sol.r2), p2))
		> cylinder->radius_sq)
		sol.r2 = -FLT_1;
	return (sol);
}

__attribute__((hot))
static t_sol2	tube_intersect(const struct s_ray *ray,
	const struct s_cylinder *cylinder)
{
	const t_real3	offset = minus3(ray->origin, cylinder->coord);
	const t_real3	tmp_a = minus3(ray->dir, \
		fmul3(cylinder->axis, dot(ray->dir, cylinder->axis)));
	const t_real3	tmp_b = minus3(offset, \
		fmul3(cylinder->axis, dot(offset, cylinder->axis)));	
	t_sol2			sol;

	sol = polynome2(dot(tmp_a, tmp_a), FLT_2 * dot(tmp_a, tmp_b), \
		dot(tmp_b, tmp_b) - cylinder->radius_sq);
	if (sol.r1 > EPSILON)
		if (dot(cylinder->axis, minus3(\
			project(ray->origin, ray->dir, sol.r1), cylinder->p1)) <= EPSILON \
			|| dot(cylinder->axis, minus3(\
				project(\
					ray->origin, ray->dir, sol.r1), cylinder->p2)) >= EPSILON)
		sol.r1 = -FLT_1;
	if (sol.r2 > EPSILON)
		if (dot(cylinder->axis, minus3(\
			project(ray->origin, ray->dir, sol.r2), cylinder->p1)) <= EPSILON \
			|| dot(cylinder->axis, minus3(project(\
				ray->origin, ray->dir, sol.r2), cylinder->p2)) >= EPSILON)
		sol.r2 = -FLT_1;
	return (sol);
}

__attribute__((hot))
t_real3	normal_tube(const struct s_cylinder *cylinder, const t_real3 hit_point)
{
	const t_real3	oc = minus3(hit_point, cylinder->coord);
	const t_real	projection = dot(oc, cylinder->axis);
	const t_real3	closest_on_axis = plus3(cylinder->coord, \
		fmul3(cylinder->axis, projection));

	return (normalize3(minus3(hit_point, closest_on_axis)));
}

__attribute__((hot))
t_hit_info	ray_hit_cylinder(const struct s_ray *ray, const void *elem)
{
	struct s_hit_info		hit;
	const struct s_cylinder	cylinder = ((struct s_elem *)elem)->u.cylinder;
	const t_real			dst_tube = \
		closest_hit_dst_sol2(tube_intersect(ray, &cylinder));

	hit.dst = closest_hit_dst_sol2(caps_intersect(ray, &cylinder));
	if (hit.dst >= EPSILON)
	{
		hit.hit_point = project(ray->origin, ray->dir, hit.dst);
		hit.normal = orient_normal(cylinder.axis, ray->dir);
	}
	if (dst_tube >= EPSILON)
	{
		if (hit.dst < EPSILON \
			|| ft_dblcmp(dst_tube, hit.dst, EPSILON) < FLT_0)
		{
			hit.dst = dst_tube;
			hit.hit_point = project(ray->origin, ray->dir, hit.dst);
			hit.normal = orient_normal(\
				normal_tube(&cylinder, hit.hit_point), ray->dir);
		}
	}
	hit.material = cylinder.material;
	hit.did_hit = (hit.dst >= EPSILON);
	return (hit);
}
