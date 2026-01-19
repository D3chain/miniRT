/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:20:27 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/19 16:20:29 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_real	plane_dst(const struct s_ray *ray, const t_real3 normal, const t_real3 point)
{
	const t_real	d = -dot(normal, point);
	
	return (dot(minus3(point, ray->origin), normal) / dot(ray->dir, normal));
}

t_hit_info	ray_hit_plane(const struct s_ray *ray, const void *elem)
{
	t_hit_info				closest_hit;
	const struct s_plane	plane = ((struct s_elem *)elem)->u.plane;
	const t_real			denom = dot(ray->dir, plane.normal);

	if (fabs(denom) < EPSILON)
		return ((t_hit_info){0});
	closest_hit.dst = dot(minus3(plane.coord, ray->origin), plane.normal) / denom;
	closest_hit.did_hit = (closest_hit.dst >= EPSILON);
	if (closest_hit.did_hit)
	{
		closest_hit.hit_point = project(ray->origin, ray->dir, closest_hit.dst);
		closest_hit.normal = orient_normal(plane.normal, ray->dir);
		closest_hit.material = plane.material;
	}
	return (closest_hit);
}
