/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 13:47:32 by cgajean           #+#    #+#             */
/*   Updated: 2025/11/20 11:58:40 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

const t_double3	project(const t_double3 origin, const t_double3 dir, const double dst)
{
	return (plus3(origin, mul3(dir, dst)));
}

static const t_sol2	caps_intersect(const struct s_ray *ray,
	const struct s_cylinder *cylinder)
{
	t_sol2			sol;
	const t_double3	p1 = project(cylinder->coord, cylinder->axis, cylinder->height / 2);
	const t_double3	p2 = project(cylinder->coord, mul3(cylinder->axis, -1.0), cylinder->height / 2);
	
	sol.n = 2;
	sol.r1 = plane_dst(ray, cylinder->axis, p1);
	if (sqdot(minus3(project(ray->origin, ray->dir, sol.r1), p1)) > pow(cylinder->radius, 2.0))
		sol.r1 = -1.0;
	sol.r2 = plane_dst(ray, cylinder->axis, p2);
	if (sqdot(minus3(project(ray->origin, ray->dir, sol.r2), p1)) > pow(cylinder->radius, 2.0))
		sol.r2 = -1.0;
	return (sol);
}

// static const t_sol2	tube_intersect(const struct s_ray *ray,
// 	const struct s_cylinder *cylinder)
// {
// 	const t_double3	offset = minus3(ray->origin, cylinder->coord);
// 	const t_double3	tmp_a = minus3(ray->dir, mul3(ray->dir, dot(ray->dir, cylinder->axis)));
// 	const t_double3	tmp_b = minus3(offset, mul3(cylinder->axis, dot(offset, cylinder->axis)));
	
// 	return (polynome2(dot(tmp_a, tmp_a), 2 * dot(tmp_a, tmp_b),
// 		dot(tmp_b, tmp_b) - pow(cylinder->radius, 2.0)));
// }

static const t_sol2	tube_intersect(const struct s_ray *ray,
	const struct s_cylinder *cylinder)
{
	const t_double3	offset = minus3(ray->origin, cylinder->coord);
	const t_double3	tmp_a = minus3(ray->dir, mul3(ray->dir, dot(ray->dir, cylinder->axis)));
	const t_double3	tmp_b = minus3(offset, mul3(cylinder->axis, dot(offset, cylinder->axis)));	
	
	/********/
	t_sol2	sol = polynome2(dot(tmp_a, tmp_a), 2 * dot(tmp_a, tmp_b),
		dot(tmp_b, tmp_b) - pow(cylinder->radius, 2.0));
	
	const t_double3	p1 = project(cylinder->coord, mul3(cylinder->axis, -1.0), cylinder->height / 2);
	const t_double3	p2 = project(cylinder->coord, cylinder->axis, cylinder->height / 2);
	// printf("%lf, %lf, %lf\n",p1.x, p1.y, p1.z);
	// printf("%lf, %lf, %lf\n\n",p2.x, p2.y, p2.z);
	if (sol.r1 > 0)
		if (dot(cylinder->axis, minus3(project(ray->origin, ray->dir, sol.r1), p1)) <= 0
			|| dot(cylinder->axis, minus3(project(ray->origin, ray->dir, sol.r1), p2)) >= 0)
		sol.r1 = -1.0;
	
	// }

	if (sol.r2 > 0)
		if (dot(cylinder->axis, minus3(project(ray->origin, ray->dir, sol.r2), p1)) <= 0
			|| dot(cylinder->axis, minus3(project(ray->origin, ray->dir, sol.r2), p2)) >= 0)
		sol.r2 = -1.0;
	/********/
	return (sol);
}

static double	cylinder_dst(const struct s_ray *ray, const struct s_cylinder *cylinder)
{
	// const t_sol2	dst_caps = caps_intersect(ray, cylinder);
	const t_sol2	dst_tube = tube_intersect(ray, cylinder);
	
	return (closest_hit_dst_sol2(dst_tube));
	// return (closest_hit_dst_dbl(closest_hit_dst_sol2(dst_caps),
	// 	closest_hit_dst_sol2(dst_tube)));
}

struct s_hit_info	ray_cylinder(const struct s_ray *ray, const void *elem)
{
	struct s_hit_info		closest_hit;
	const struct s_cylinder	cylinder = ((struct s_elem *)elem)->u.cylinder;

	ft_bzero(&closest_hit, sizeof(closest_hit));	
	closest_hit.dst = cylinder_dst(ray, &cylinder);
	closest_hit.did_hit = (closest_hit.dst > 0.0);
	closest_hit.color_material = cylinder.color;
	return (closest_hit);
}

