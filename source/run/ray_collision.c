/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:08:41 by echatela          #+#    #+#             */
/*   Updated: 2025/11/20 16:38:25 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	plane_dst(const struct s_ray *ray, const t_double3 normal, const t_double3 point)
{
	const double	d = -dot(normal, point);
	
	return (dot(minus3(point, ray->origin), normal) / dot(ray->dir, normal));
}

struct s_hit_info	ray_plane(const struct s_ray *ray, const void *elem)
{
	struct s_hit_info		closest_hit;
	const struct s_plane	plane = ((struct s_elem *)elem)->u.plane;

	ft_bzero(&closest_hit, sizeof(closest_hit));
	closest_hit.dst = plane_dst(ray, plane.normal, plane.coord);
	closest_hit.did_hit = (closest_hit.dst > 0);
	closest_hit.color_material = plane.color;
	return (closest_hit);
}

struct s_hit_info	ray_sphere(const struct s_ray *ray, const void *elem)
{
	struct s_hit_info			closest_hit;
	const struct s_sphere		sphere = ((struct s_elem *)elem)->u.sphere;
	const t_double3				offset = minus3(ray->origin, sphere.coord);
	const t_sol2				dst = polynome2(dot(ray->dir, ray->dir),
				2 * dot(offset, ray->dir),
				dot(offset, offset) - pow(sphere.radius, 2.0));
	
	ft_bzero(&closest_hit, sizeof(closest_hit));
	if (dst.n)
	{
		if (dst.n == 1)
			closest_hit.dst = dst.r1;
		else
			closest_hit.dst = closest_hit_dst_sol2(dst);
		closest_hit.did_hit = (closest_hit.dst > 0);
		closest_hit.color_material = sphere.color;
	}
	return (closest_hit);
}

struct s_hit_info	compute_ray_collision(struct s_ray *ray, struct s_elem *elems, int n)
{
	static struct s_hit_info	(*ray_func[])(const struct s_ray *, const void*) = {ray_plane, ray_sphere, ray_cylinder};
	struct s_hit_info	closest_hit;
	struct s_hit_info	hit_point;
	int					i;

	ft_bzero(&closest_hit, sizeof(closest_hit));
	ft_bzero(&hit_point, sizeof(hit_point));
	i = -1;
	while (++i < n)
	{
		hit_point = ray_func[elems[i].type](ray, &elems[i]);
		if (hit_point.did_hit)
		{
			if (closest_hit.did_hit && closest_hit.dst > hit_point.dst)
				closest_hit = hit_point;
			else if (!closest_hit.did_hit)
				closest_hit = hit_point;
		}
	}
	return (closest_hit);
}

int	ray_color(struct s_ray *ray, struct s_elem *elems, int n)
{
	return (compute_ray_collision(ray, elems, n).color_material);
}
