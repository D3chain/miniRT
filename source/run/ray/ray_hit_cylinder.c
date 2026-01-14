/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:47:32 by cgajean           #+#    #+#             */
/*   Updated: 2025/12/08 17:56:38 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

__attribute__((hot))
static const t_sol2	caps_intersect(const struct s_ray *ray,
	const struct s_cylinder *cylinder)
{
	t_sol2			sol;
	const t_real3	p1 = project(cylinder->coord, cylinder->axis,
		cylinder->height / 2);
	const t_real3	p2 = project(cylinder->coord,
		fmul3(cylinder->axis, -1.0), cylinder->height / 2);
	const t_real	rdot = dot(cylinder->axis, ray->dir);
	
	if (ft_dblcmp(rdot, 0.0, EPSILON) == 0.0)
		return (sol.n = 0, sol);
	sol.n = 2;
	sol.r1 = plane_dst(ray, cylinder->axis, p1);
	if (sqdot(minus3(project(ray->origin, ray->dir, sol.r1), p1))
		> cylinder->radius * cylinder->radius)
		sol.r1 = -1.0;
	sol.r2 = plane_dst(ray, cylinder->axis, p2);
	if (sqdot(minus3(project(ray->origin, ray->dir, sol.r2), p2))
		> cylinder->radius_sq)
		sol.r2 = -1.0;
	return (sol);
}

__attribute__((hot))
static const t_sol2	tube_intersect(const struct s_ray *ray,
	const struct s_cylinder *cylinder)
{
	const t_real3	offset = minus3(ray->origin, cylinder->coord);
	const t_real3	tmp_a = minus3(ray->dir, fmul3(cylinder->axis, dot(ray->dir, cylinder->axis)));
	const t_real3	tmp_b = minus3(offset, fmul3(cylinder->axis, dot(offset, cylinder->axis)));	
	
	t_sol2	sol = polynome2(dot(tmp_a, tmp_a), 2 * dot(tmp_a, tmp_b),
		dot(tmp_b, tmp_b) - cylinder->radius_sq);
	
	if (sol.r1 > 0.0)
		if (dot(cylinder->axis, minus3(project(ray->origin, ray->dir, sol.r1), cylinder->p1)) <= 0
			|| dot(cylinder->axis, minus3(project(ray->origin, ray->dir, sol.r1), cylinder->p2)) >= 0)
		sol.r1 = -1.0;

	if (sol.r2 > 0.0)
		if (dot(cylinder->axis, minus3(project(ray->origin, ray->dir, sol.r2), cylinder->p1)) <= 0
			|| dot(cylinder->axis, minus3(project(ray->origin, ray->dir, sol.r2), cylinder->p2)) >= 0)
		sol.r2 = -1.0;
	return (sol);
}

t_real3	normal_tube(const struct s_cylinder *cylinder, const t_real3 hit_point)
{
	const t_real3	oc = minus3(hit_point, cylinder->coord);
	t_real			projection = dot(oc, cylinder->axis);
	const t_real3	closest_on_axis = plus3(cylinder->coord, fmul3(cylinder->axis, projection));
	
	return (normalize3(minus3(hit_point, closest_on_axis)));
}

t_hit_info	ray_hit_cylinder(const struct s_ray *ray, const void *elem)
{
	struct s_hit_info		closest_hit;
	const struct s_cylinder	cylinder = ((struct s_elem *)elem)->u.cylinder;
	const t_real			dst_tube = closest_hit_dst_sol2(tube_intersect(ray, &cylinder));

	closest_hit.dst = closest_hit_dst_sol2(caps_intersect(ray, &cylinder));
	if (closest_hit.dst >= EPSILON)
	{
		closest_hit.hit_point = project(ray->origin, ray->dir, closest_hit.dst);
		closest_hit.normal = orient_normal(cylinder.axis, ray->dir);
	}
	if (dst_tube >= EPSILON)
	{
		if (closest_hit.dst < EPSILON || ft_dblcmp(dst_tube, closest_hit.dst, EPSILON) < 0.0)
		{
			closest_hit.dst = dst_tube;
			closest_hit.hit_point = project(ray->origin, ray->dir, closest_hit.dst);
			closest_hit.normal = orient_normal(normal_tube(&cylinder, closest_hit.hit_point), ray->dir); 
		}
	}
	closest_hit.material = cylinder.material;
	closest_hit.did_hit = (closest_hit.dst >= EPSILON);
	return (closest_hit);
}
