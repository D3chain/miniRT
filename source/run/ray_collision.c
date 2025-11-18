/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:08:41 by echatela          #+#    #+#             */
/*   Updated: 2025/11/18 16:16:49 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

const struct s_poly2_root	polynome2(double a, double b, double c)
{
	const double		dis = pow(b, 2.0) - 4 * a * c;
	struct s_poly2_root	res;

	if (dis < 0)
	{
		res.n = 0;
	}
	else if (dis == 0)
	{
		res.n = 1;
		res.r1 = (-b) / (2 * a);
	}
	else
	{
		res.n = 2;
		res.r1 = (-b + sqrt(dis)) / (2 * a);
		res.r2 = (-b - sqrt(dis)) / (2 * a);
	}
	return (res);
}

double	closest_hit_dst(const double a, const double b)
{
	if (a <= 0 && b > 0)
		return (b);
	else if (b <= 0 && a > 0)
		return (a);
	else
		return (fmin(a, b));
}

double	plane_dst(const struct s_ray *ray, const struct s_plane *plane)
{
	const t_double3	normal = plane->normal;
	const t_double3	point = plane->coord;
	const double	d = -(normal.x * point.x +
		normal.y * point.y + normal.z * point.z);
	
	return (dot(minus3(point, ray->origin), normal) / dot(ray->dir, normal));
}

struct s_hit_info	ray_plane(const struct s_ray *ray, const void *elem)
{
	struct s_hit_info		closest_hit;
	const struct s_plane	plane = ((struct s_elem *)elem)->u.plane;

	ft_bzero(&closest_hit, sizeof(closest_hit));	
	closest_hit.dst = plane_dst(ray, &plane);
	closest_hit.did_hit = (closest_hit.dst > 0);
	closest_hit.color_material = plane.color;
	return (closest_hit);
}

struct s_hit_info	ray_sphere(const struct s_ray *ray, const void *elem)
{
	struct s_hit_info			closest_hit;
	const struct s_sphere		sphere = ((struct s_elem *)elem)->u.sphere;
	const t_double3				off_ray_origin = minus3(ray->origin, sphere.coord);
	const struct s_poly2_root	dst = polynome2(dot(ray->dir, ray->dir),
				2 * dot(off_ray_origin, ray->dir),
				dot(off_ray_origin, off_ray_origin) - pow(sphere.radius, 2.0)); 
	
	ft_bzero(&closest_hit, sizeof(closest_hit));
	if (dst.n)
	{
		if (dst.n == 1)
			closest_hit.dst = dst.r1;
		else
			closest_hit.dst = closest_hit_dst(dst.r1, dst.r2);
		closest_hit.did_hit = (closest_hit.dst > 0);
		closest_hit.color_material = sphere.color;
	}
	return (closest_hit);
}

struct s_hit_info	ray_cylinder(const struct s_ray *ray, const void *elem)
{
	struct s_hit_info			closest_hit;
	const struct s_sphere		sphere = ((struct s_elem *)elem)->u.sphere;
	
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
