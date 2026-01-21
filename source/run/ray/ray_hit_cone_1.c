/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit_cone_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 10:46:36 by echatela          #+#    #+#             */
/*   Updated: 2026/01/21 14:26:54 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

__attribute__((always_inline, hot))
inline void
	compute_cone_quadratic(const t_cone *cone, const t_ray *ray, \
											t_real3 x, t_real coefs[3])
{
	t_real	dir_dot_axis;
	t_real	x_dot_axis;

	dir_dot_axis = dot(ray->dir, cone->axis);
	x_dot_axis = dot(x, cone->axis);
	coefs[0] = dir_dot_axis * dir_dot_axis - cone->cos2_theta;
	coefs[1] = FLT_2 \
		* (dir_dot_axis * x_dot_axis - cone->cos2_theta * dot(ray->dir, x));
	coefs[2] = x_dot_axis * x_dot_axis - cone->cos2_theta * dot(x, x);
}

__attribute__((always_inline, hot))
inline bool	solve_quadratic(t_real coefs[3], t_real *t1, t_real *t2)
{
	t_real	discriminant;
	t_real	sqrt_disc;
	t_real	tmp;

	discriminant = coefs[1] * coefs[1] - FLT_4 * coefs[0] * coefs[2];
	if (discriminant < EPSILON)
		return (false);
	sqrt_disc = sqrt(discriminant);
	*t1 = -(sqrt_disc + coefs[1]) / (FLT_2 * coefs[0]);
	*t2 = (sqrt_disc - coefs[1]) / (FLT_2 * coefs[0]);
	if (*t1 > *t2)
	{
		tmp = *t1;
		*t1 = *t2;
		*t2 = tmp;
	}
	return (true);
}

__attribute__((always_inline, hot))
inline t_hit_info	ray_hit_cone(const t_ray *ray, const void *elem)
{
	const t_cone	cone = ((t_shape *)elem)->u.cone;
	t_hit_info		body_hit;
	t_hit_info		cap_hit;

	body_hit = intersect_cone_body(ray, &cone);
	cap_hit = intersect_cone_cap(ray, &cone);
	if (body_hit.did_hit && cap_hit.did_hit)
	{
		if (body_hit.dst < cap_hit.dst)
			return (body_hit);
		return (cap_hit);
	}
	if (body_hit.did_hit)
		return (body_hit);
	if (cap_hit.did_hit)
		return (cap_hit);
	return ((t_hit_info){0});
}
