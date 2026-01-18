/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_bvh_coord.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:51:51 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/17 21:03:41 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	update_shapes_coord(t_bvh_base *tree, t_int2 offset)
{
	int				n;
	int				n_elem;
	struct s_elem	*e;
	
	if (tree->type == NODE_BOX)
	{
		update_shapes_coord(((t_bvh_node *)tree)->left, offset);
		update_shapes_coord(((t_bvh_node *)tree)->right, offset);
	}
	else
	{
		n = 0;
		n_elem = ((t_bvh_elem_box *)tree)->n_elems;
		while (n < n_elem)
		{
			e = &((t_bvh_elem_box *)tree)->elems[n];
			e->u.any.coord.x += offset.x / OBJ_DRAG_DIV_FACTOR;
			e->u.any.coord.y -= offset.y / OBJ_DRAG_DIV_FACTOR;
			++n;
		}
	}
}
