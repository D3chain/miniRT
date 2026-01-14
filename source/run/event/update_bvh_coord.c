/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_bvh_coord.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:51:51 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/14 17:33:23 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	update_camera(struct s_camera *camera, int value)
{
	camera->focal_center.z += value;
}

void	bvh_update_coord(t_bvh_base *tree, t_int2 offset)
{
	int				n;
	int				n_elem;
	struct s_elem	*e;
	
	if (tree->type == NODE_BOX)
	{
		bvh_update_coord(((t_bvh_node *)tree)->left, offset);
		bvh_update_coord(((t_bvh_node *)tree)->right, offset);
	}
	else
	{
		n = 0;
		n_elem = ((t_bvh_elem_box *)tree)->n_elems;
		while (n < n_elem)
		{
			e = &((t_bvh_elem_box *)tree)->elems[n];
			e->u.any.coord.x += (t_real) offset.x / 5;
			e->u.any.coord.y -= (t_real) offset.y / 5;
			++n;
		}
	}
}
