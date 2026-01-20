/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shapes_coord.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:51:51 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/20 20:27:14 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

__attribute__((always_inline))
static inline void	traverse_bvh(
	struct s_camera *camera, t_bvh_elem_box *tree, t_int2 offset)
{
	const t_real3	vec_offset = {
		.x = (camera->dir_right.x * offset.x + camera->dir_up.x * offset.y) \
			* -OBJ_DRAG_DIV_FACTOR,
		.y = (camera->dir_right.y * offset.x + camera->dir_up.y * offset.y) \
			* -OBJ_DRAG_DIV_FACTOR,
		.z = (camera->dir_right.z * offset.x + camera->dir_up.z * offset.y) \
			* -OBJ_DRAG_DIV_FACTOR,
	};
	int				n_elem;
	int				n;
	struct s_elem	*e;

	n = 0;
	n_elem = tree->n_elems;
	while (n < n_elem)
	{
		e = &tree->elems[n];
		e->u.any.coord = plus3(e->u.any.coord, vec_offset);
		++n;
	}
}

void	update_shapes_coord(
	struct s_camera *camera, t_bvh_base *tree, t_int2 offset)
{
	if (tree->type == NODE_BOX)
	{
		update_shapes_coord(camera, ((t_bvh_node *)tree)->left, offset);
		update_shapes_coord(camera, ((t_bvh_node *)tree)->right, offset);
	}
	else
		traverse_bvh(camera, (t_bvh_elem_box *) tree, offset);
}
