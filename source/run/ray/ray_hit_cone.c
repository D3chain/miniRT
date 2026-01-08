/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit_cone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 10:46:36 by echatela          #+#    #+#             */
/*   Updated: 2026/01/08 11:47:11 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static const double	cap_intersect(const struct s_ray *ray,
	const struct s_cone *cone)
{
	double			sol;
	const double	rdot = dot(cone->axis, ray->dir);
	
	if (ft_dblcmp(rdot, 0.0, EPSILON) == 0.0)
		return (-1.0);
	sol = plane_dst(ray, cone->axis, cone->p1);
	if (sqdot(minus3(project(ray->origin, ray->dir, sol), cone->p1))
		> cone->radius_sq)
		return (-1.0);
	return (sol);
}

struct s_co
{
	t_double3	offset;
	double		d_dot_axis;
	double		off_dot_axis;
	t_double3	d_perp;
	t_double3	off_perp;
};

static struct s_co	get_co(const struct s_ray *ray,
	const struct s_cone *cone)
{
	struct s_co	co;

	co.offset = minus3(ray->origin, cone->p2);
	co.d_dot_axis = dot(ray->dir, cone->axis);
	co.off_dot_axis = dot(co.offset, cone->axis);
	co.d_perp = minus3(ray->dir, mul3(cone->axis, co.d_dot_axis));
	co.off_perp = minus3(co.offset, mul3(cone->axis, co.off_dot_axis));
	return (co);
}

static const t_sol2	cornet_intersect(const struct s_ray *ray,
	const struct s_cone *cone)
{
	const struct s_co	co = get_co(ray, cone);
	const double		k = pow(cone->radius / cone->height, 2.0);
	const double		a = dot(co.d_perp, co.d_perp) - k * pow(co.d_dot_axis, 2.0);
	const double		b = 2.0 * (dot(co.d_perp, co.off_perp) - k * co.d_dot_axis * co.off_dot_axis);
	const double		c = dot(co.off_perp, co.off_perp) - k * pow(co.off_dot_axis, 2.0);
	t_sol2				sol = polynome2(a, b, c);

	if (sol.r1 > EPSILON)
		if (dot(minus3(project(ray->origin, ray->dir, sol.r1), cone->p2), cone->axis) < EPSILON
			|| dot(minus3(project(ray->origin, ray->dir, sol.r1), cone->p2), cone->axis) > cone->height)
			sol.r1 = -1.0;
	if (sol.r2 > EPSILON)
		if (dot(minus3(project(ray->origin, ray->dir, sol.r2), cone->p2), cone->axis) < EPSILON
			|| dot(minus3(project(ray->origin, ray->dir, sol.r2), cone->p2), cone->axis) > cone->height)
			sol.r2 = -1.0;
	return (sol);
}

t_double3	normal_cornet(const struct s_cone *cone, const t_double3 hit_point)
{
	const t_double3	v = minus3(hit_point, cone->p1);
	const double	h = dot(v, cone->axis);
	const t_double3	v_perp = minus3(v, mul3(cone->axis , h));
	const double	k = cone->radius / cone->height;
	return (normalize3(minus3(v_perp, mul3(cone->axis, k * h))));
}

struct s_hit_info	ray_hit_cone(const struct s_ray *ray, const void *elem)
{
	struct s_hit_info	closest_hit;
	const struct s_cone	cone = ((struct s_elem *)elem)->u.cone;
	const double		dst_cornet = closest_hit_dst_sol2(cornet_intersect(ray, &cone));

	ft_bzero(&closest_hit, sizeof(closest_hit));
	closest_hit.dst = cap_intersect(ray, &cone);
	if (closest_hit.dst >= EPSILON)
	{
		closest_hit.hit_point = project(ray->origin, ray->dir, closest_hit.dst);
		closest_hit.normal = orient_normal(cone.axis, ray->dir);
	}
	if (dst_cornet >= EPSILON)
	{
		if (closest_hit.dst < EPSILON || ft_dblcmp(dst_cornet, closest_hit.dst, EPSILON) < 0.0)
		{
			closest_hit.dst = dst_cornet;
			closest_hit.hit_point = project(ray->origin, ray->dir, closest_hit.dst);
			closest_hit.normal = orient_normal(normal_cornet(&cone, closest_hit.hit_point), ray->dir);
		}
	}
	closest_hit.material = cone.material;
	closest_hit.did_hit = (closest_hit.dst >= EPSILON);
	return (closest_hit);
}