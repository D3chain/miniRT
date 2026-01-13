/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   any_hit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 13:35:29 by fox               #+#    #+#             */
/*   Updated: 2026/01/13 16:48:26 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	check_leaf_shadow(t_bvh_elem_box *box, const t_ray *ray, 
                                t_real max_dist)
{
	static struct s_hit_info	(*ray_hit_func[])(const struct s_ray *,
		const void*) = {ray_hit_plane, ray_hit_sphere, 
			ray_hit_cylinder, ray_hit_cone};
	struct s_hit_info			hit;
	int							i;

	i = -1;
	while (++i < box->n_elems)
	{
		hit = ray_hit_func[box->elems[i].type](ray, &box->elems[i]);
		if (hit.did_hit && hit.dst > 0.001 && hit.dst < max_dist)
			return (true);
	}
	return (false);
}

bool	bvh_any_hit(t_bvh_base *tree, const t_ray *ray, t_real max_dist)
{
	if (!collision_aabb_base(tree, (t_ray *)ray))
		return (false);
	
	if (tree->type == NODE_BOX)
	{
		if (bvh_any_hit(((t_bvh_node *)tree)->left, ray, max_dist))
			return (true);
		if (bvh_any_hit(((t_bvh_node *)tree)->right, ray, max_dist))
			return (true);
		return (false);
	}
	else
		return (check_leaf_shadow((t_bvh_elem_box *)tree, ray, max_dist));
}

bool	elem_inf_any_hit(const struct s_scene *scene, const t_ray *ray, t_real max_dist)
{
	struct s_hit_info	hit;
	int					i;
	
	i = -1;
	while (++i < scene->n_elem_inf)
	{
		hit = ray_hit_plane(ray, &scene->elems_inf[i]);
		if (hit.did_hit && hit.dst > 0.001 && hit.dst < max_dist)
			return (true);
	}
	return (false);
}
