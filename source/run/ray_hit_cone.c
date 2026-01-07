/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit_cone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 10:46:36 by echatela          #+#    #+#             */
/*   Updated: 2026/01/07 13:09:39 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static const double	cap_intersect(const struct s_ray *ray,
	const struct s_cone *cone)
{
	double			sol;
	const t_double3	p = cone->coord;
	const double	rdot = dot(cone->axis, ray->dir);
	
	if (ft_dblcmp(rdot, 0.0, EPSILON) == 0.0)
		return (-1.0);
	sol = plane_dst(ray, cone->axis, p);
	if (sqdot(minus3(project(ray->origin, ray->dir, sol), p)) > pow(cylinder->radius, 2.0))
		sol.r1 = -1.0;
	sol.r2 = plane_dst(ray, cylinder->axis, p2);
	if (sqdot(minus3(project(ray->origin, ray->dir, sol.r2), p2)) > pow(cylinder->radius, 2.0))
		sol.r2 = -1.0;
	return (sol);
}

struct s_hit_info	ray_hit_cone(const struct s_ray *ray, const void *elem)
{
	struct s_hit_info	closest_hit;
	const struct s_cone	cone = ((struct s_elem *)elem)->u.cone;
	const double		
}