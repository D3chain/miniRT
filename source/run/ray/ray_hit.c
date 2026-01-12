/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:08:41 by echatela          #+#    #+#             */
/*   Updated: 2026/01/12 14:00:03 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

struct s_hit_info	ray_hit(t_bvh_elem_box *box, const t_ray *ray)
{
	static struct s_hit_info	(*ray_hit_func[])(const struct s_ray *,
		const void*) = {ray_hit_plane, ray_hit_sphere, 
			ray_hit_cylinder, ray_hit_cone};
	struct s_hit_info			closest_hit;
	struct s_hit_info			hit_point;
	int							i;

	ft_bzero(&closest_hit, sizeof(closest_hit));
	ft_bzero(&hit_point, sizeof(hit_point));
	i = -1;
	while (++i < box->n_elems)
	{
		hit_point = ray_hit_func[box->elems[i].type](ray, &box->elems[i]);
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

// struct s_hit_info	ray_hit(const t_ray *ray, struct s_elem *elems, int n)
// {
// 	static struct s_hit_info	(*ray_hit_func[])(const struct s_ray *,
// 		const void*) = {ray_hit_plane, ray_hit_sphere, 
// 			ray_hit_cylinder, ray_hit_cone};
// 	struct s_hit_info			closest_hit;
// 	struct s_hit_info			hit_point;
// 	int							i;

// 	ft_bzero(&closest_hit, sizeof(closest_hit));
// 	ft_bzero(&hit_point, sizeof(hit_point));
// 	i = -1;
// 	while (++i < n)
// 	{
// 		hit_point = ray_hit_func[elems[i].type](ray, &elems[i]);
// 		if (hit_point.did_hit)
// 		{
// 			if (closest_hit.did_hit && closest_hit.dst > hit_point.dst)
// 				closest_hit = hit_point;
// 			else if (!closest_hit.did_hit)
// 				closest_hit = hit_point;
// 		}
// 	}
// 	return (closest_hit);
// }
