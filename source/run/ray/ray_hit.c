/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:08:41 by echatela          #+#    #+#             */
/*   Updated: 2026/01/14 00:12:10 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

__attribute__((hot))
t_hit_info	ray_hit(t_bvh_elem_box *box, const t_ray *ray)
{
	static t_hit_info	(*ray_hit_func[])(const struct s_ray *,	const void*) = {
		ray_hit_plane,
		ray_hit_sphere,
		ray_hit_cylinder, 
		ray_hit_cone
	};
	t_hit_info			closest_hit;
	t_hit_info			hit_point;
	int					i;

	closest_hit.did_hit = false;
	i = -1;
	while (++i < box->n_elems)
	{
		hit_point = ray_hit_func[box->elems[i].type](ray, &box->elems[i]);
		if (hit_point.did_hit)
			if (!closest_hit.did_hit || hit_point.dst < closest_hit.dst)
		        closest_hit = hit_point;
	}
	return (closest_hit);
}
