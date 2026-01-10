/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:10:09 by fox               #+#    #+#             */
/*   Updated: 2026/01/10 13:35:06 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit_info	bvh_traverse(t_bvh_base *tree, const t_ray *ray)
{
	t_hit_info	hit_left;
	t_hit_info	hit_right;

	// Initialiser à "pas de hit"
	ft_bzero(&hit_left, sizeof(hit_left));
	ft_bzero(&hit_right, sizeof(hit_right));

	if (tree->type == NODE_BOX)
	{
		// CRITIQUE : Tester la bbox AVANT de descendre
		if (!collision_aabb((t_bvh_node *)tree, (t_ray *)ray))
			return (hit_left);  // Retourner "pas de hit"
		
		// Tester les enfants seulement si leurs bbox sont touchées
		if (collision_aabb((t_bvh_node *)(((t_bvh_node *)tree)->left), (t_ray *)ray))
			hit_left = bvh_traverse(((t_bvh_node *)tree)->left, ray);
		
		if (collision_aabb((t_bvh_node *)(((t_bvh_node *)tree)->right), (t_ray *)ray))
			hit_right = bvh_traverse(((t_bvh_node *)tree)->right, ray);
		
		// Garder le plus proche
		if (hit_left.did_hit && hit_right.did_hit)
			return (hit_left.dst < hit_right.dst ? hit_left : hit_right);
		else if (hit_left.did_hit)
			return (hit_left);
		else
			return (hit_right);
	}
	else
		return (ray_hit((t_bvh_elem_box *)tree, ray));
}

inline t_color_linear	trace(struct s_scene *scene, const t_ray *ray)
{
	t_hit_info	hit_info;

	hit_info = bvh_traverse(scene->bvh_root, ray);
	if (!hit_info.did_hit)
		return (srgb_to_linear_color((t_color){.value = BLACK}));
	return (phong_effect(scene, &hit_info));
}

