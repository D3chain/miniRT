/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:27:06 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/19 11:14:59 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit_info	ray_hit_sphere(const struct s_ray *ray, const void *elem)
{
	t_hit_info					closest_hit;
	const struct s_sphere		sphere = ((struct s_elem *)elem)->u.sphere;
	const t_real3				offset = minus3(ray->origin, sphere.coord);
	const t_sol2				dst = polynome2(dot(ray->dir, ray->dir),
				FLT_2 * dot(offset, ray->dir),
				dot(offset, offset) - sphere.radius_sq);
	
	closest_hit.did_hit = false;
	if (dst.n)
	{
		closest_hit.dst = closest_hit_dst_sol2(dst);
		closest_hit.did_hit = (closest_hit.dst >= EPSILON);
		if (closest_hit.did_hit)
		{
			closest_hit.hit_point = project(ray->origin, ray->dir, closest_hit.dst);
			closest_hit.normal = orient_normal(normalize3(minus3(closest_hit.hit_point, sphere.coord)), ray->dir);
			closest_hit.material = sphere.material;
		}
	}
	return (closest_hit);
}
