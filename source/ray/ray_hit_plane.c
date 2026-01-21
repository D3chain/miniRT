/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:20:27 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/21 17:27:07 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

__attribute__((hot))
t_real
	plane_dst(const t_ray *ray, const t_real3 normal, \
		const t_real3 point)
{
	return (dot(minus3(point, ray->origin), normal) / dot(ray->dir, normal));
}

__attribute__((hot))
t_hit_info	ray_hit_plane(const t_ray *ray, const void *elem)
{
	t_hit_info		closest_hit;
	const t_plane	plane = ((t_shape *)elem)->u_.plane;
	const t_real	denom = dot(ray->dir, plane.normal);

	if (fabs(denom) < EPSILON)
		return ((t_hit_info){0});
	closest_hit.dst = dot(\
		minus3(plane.coord, ray->origin), plane.normal) / denom;
	closest_hit.did_hit = (closest_hit.dst >= EPSILON);
	if (closest_hit.did_hit)
	{
		closest_hit.hit_point = project(ray->origin, ray->dir, closest_hit.dst);
		closest_hit.normal = orient_normal(plane.normal, ray->dir);
		closest_hit.material = plane.material;
	}
	return (closest_hit);
}
