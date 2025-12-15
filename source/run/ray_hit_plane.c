/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:27:42 by cgajean           #+#    #+#             */
/*   Updated: 2025/12/15 11:27:52 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	plane_dst(const struct s_ray *ray, const t_double3 normal, const t_double3 point)
{
	const double	d = -dot(normal, point);
	
	return (dot(minus3(point, ray->origin), normal) / dot(ray->dir, normal));
}

struct s_hit_info	ray_hit_plane(const struct s_ray *ray, const void *elem)
{
	struct s_hit_info		closest_hit;
	const struct s_plane	plane = ((struct s_elem *)elem)->u.plane;

	ft_bzero(&closest_hit, sizeof(closest_hit));
	closest_hit.dst = plane_dst(ray, plane.normal, plane.coord);
	closest_hit.did_hit = (closest_hit.dst >= EPSILON);
	if (closest_hit.did_hit)
	{
		closest_hit.hit_point = project(ray->origin, ray->dir, closest_hit.dst);
		closest_hit.normal = orient_normal(plane.normal, ray->dir);
		closest_hit.color_material = plane.material.color;
	}
	return (closest_hit);
}
