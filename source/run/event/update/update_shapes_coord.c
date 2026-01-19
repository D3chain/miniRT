/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shapes_coord.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:51:51 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/19 12:55:33 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	update_shapes_coord(struct s_camera *camera, t_bvh_base *tree, t_int2 offset)
{
	int				n;
	int				n_elem;
	struct s_elem	*e;
	const t_real3	vec_offset = {
		.x = (camera->dir_right.x * offset.x + camera->dir_up.x * offset.y) * -OBJ_DRAG_DIV_FACTOR,
		.y = (camera->dir_right.y * offset.x + camera->dir_up.y * offset.y) * -OBJ_DRAG_DIV_FACTOR,
		.z = (camera->dir_right.z * offset.x + camera->dir_up.z * offset.y) * -OBJ_DRAG_DIV_FACTOR,
	};
	
	if (tree->type == NODE_BOX)
	{
		update_shapes_coord(camera, ((t_bvh_node *)tree)->left, offset);
		update_shapes_coord(camera, ((t_bvh_node *)tree)->right, offset);
	}
	else
	{
		n = 0;
		n_elem = ((t_bvh_elem_box *)tree)->n_elems;
		while (n < n_elem)
		{
			e = &((t_bvh_elem_box *)tree)->elems[n];
			e->u.any.coord = plus3(e->u.any.coord, vec_offset);
			++n;
		}
	}
}
