/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_bvh_coord.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:51:51 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/15 17:30:07 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	update_cam_pos_xy(struct s_camera *camera, t_real2 value)
{
	camera->focal_center.x += value.x;
	camera->focal_center.y += value.y;
}

void	update_cam_dir_xy(struct s_camera *camera, t_real2 value)
{
	camera->dir.x += value.x;
	camera->dir.y += value.y;
}

void	update_camera_z(struct s_camera *camera, t_real value)
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
