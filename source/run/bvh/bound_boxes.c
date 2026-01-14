/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bound_boxes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 11:39:21 by fox               #+#    #+#             */
/*   Updated: 2026/01/14 13:45:41 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_boundbox	merge_boxes(t_boundbox left, t_boundbox right)
{
	return ((t_boundbox){
		.beg.x = fmin(left.beg.x, right.beg.x),
		.beg.y = fmin(left.beg.y, right.beg.y),
		.beg.z = fmin(left.beg.z, right.beg.z),
		.end.x = fmax(left.end.x, right.end.x),
		.end.y = fmax(left.end.y, right.end.y),
		.end.z = fmax(left.end.z, right.end.z)
	});
}

void	bound_boxes(t_bvh_base *node)
{
	struct s_elem	*elems;
	int				n_elems;
	int				i;

	if (node->type == NODE_BOX)
	{
		bound_boxes((t_bvh_base *)((t_bvh_node *)node)->left);
		bound_boxes((t_bvh_base *)((t_bvh_node *)node)->right);
		((t_bvh_node *)node)->bbox = merge_boxes(((t_bvh_node *)node)->left->bbox, ((t_bvh_node *)node)->right->bbox);
	}
	else
	{
		elems = ((t_bvh_elem_box *)node)->elems;
		n_elems = ((t_bvh_elem_box *)node)->n_elems;
		node->bbox = elem_bounding_box(&elems[0]);
		i = 0;
		while (++i < n_elems)
			node->bbox = merge_boxes(node->bbox, elem_bounding_box(&elems[i]));
	}
}
