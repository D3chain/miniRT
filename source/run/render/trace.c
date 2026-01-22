/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:25:04 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/22 11:58:16 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_hit_info	bvh_hit(t_bvh_base *tree, t_ray *ray);

__attribute__((hot))
static inline t_hit_info	node_recursion(t_bvh_base *node, t_ray *ray)
{
	t_hit_info	hit_left;
	t_hit_info	hit_right;

	hit_left.did_hit = false;
	if (!collision_aabb((t_bvh_node *)node, ray))
		return (hit_left);
	if (collision_aabb((t_bvh_node *)(((t_bvh_node *)node)->left), ray))
		hit_left = bvh_hit(((t_bvh_node *)node)->left, ray);
	hit_right.did_hit = false;
	if (collision_aabb((t_bvh_node *)(((t_bvh_node *)node)->right), ray))
		hit_right = bvh_hit(((t_bvh_node *)node)->right, ray);
	if (hit_left.did_hit && hit_right.did_hit)
	{
		if (hit_left.dst < hit_right.dst)
			return (hit_left);
		else
			return (hit_right);
	}
	else if (hit_left.did_hit)
		return (hit_left);
	else
		return (hit_right);
}

__attribute__((always_inline, hot))
static inline t_hit_info	bvh_hit(t_bvh_base *tree, t_ray *ray)
{
	if (tree->type == NODE_BOX)
		return (node_recursion(tree, ray));
	else
		return (ray_hit((t_bvh_elem_box *)tree, ray));
}

__attribute__((always_inline, hot))
inline t_hit_info	elem_inf_hit(t_scene *scene, t_ray *ray)
{
	t_hit_info	hit_point;
	t_hit_info	closest_hit;
	int			i;

	closest_hit = ray_hit_plane(ray, &scene->elems_inf[0]);
	i = 1;
	while (i < scene->n_elem_inf)
	{
		hit_point = ray_hit_plane(ray, &scene->elems_inf[i++]);
		if (!closest_hit.did_hit)
			closest_hit = hit_point;
		else if (hit_point.did_hit && hit_point.dst < closest_hit.dst)
			closest_hit = hit_point;
	}
	return (closest_hit);
}

__attribute__((always_inline, hot))
static inline t_hit_info	cmp_hit_info(t_hit_info a, t_hit_info b)
{
	if (!a.did_hit && !b.did_hit)
		return ((t_hit_info){0});
	else if (a.did_hit && !b.did_hit)
		return (a);
	else if (!a.did_hit && b.did_hit)
		return (b);
	else if (a.dst < b.dst)
		return (a);
	else
		return (b);
}

__attribute__((hot))
t_color_lin	trace(t_scene *scene, t_ray *ray)
{
	t_hit_info	hit_info;

	hit_info = bvh_hit(scene->bvh_root, ray);
	if (scene->n_elem_inf)
		hit_info = cmp_hit_info(hit_info, elem_inf_hit(scene, ray));
	if (!hit_info.did_hit)
		return ((t_color_lin){BLACK});
	return (phong_effect(scene, &hit_info));
}
