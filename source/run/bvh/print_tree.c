/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 11:37:33 by fox               #+#    #+#             */
/*   Updated: 2026/01/14 17:29:31 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_tree(t_bvh_base *root, int depth)
{
	if (root->type == NODE_BOX)
	{
		printf("Depth #%d : NODE_BOX\n", depth);
		printf("\tLeft : %s\n", ((t_bvh_node *)root)->left->type == NODE_BOX ? "NODE_BOX" : "ELEM_BOX");
		print_real3(((t_bvh_node *)root)->left->bbox.beg, "\t\tdeb: ");
		print_real3(((t_bvh_node *)root)->left->bbox.end, "\t\tend: ");
		
		
		printf("\tRight : %s\n", ((t_bvh_node *)root)->right->type == NODE_BOX ? "NODE_BOX" : "ELEM_BOX");
		print_real3(((t_bvh_node *)root)->right->bbox.beg, "\t\tdeb: ");
		print_real3(((t_bvh_node *)root)->right->bbox.end, "\t\tend: ");		

		print_tree((t_bvh_base*)(((t_bvh_node *)root)->left), depth + 1);
		print_tree((t_bvh_base*)(((t_bvh_node *)root)->right), depth + 1);		
	}
	else
	{
		printf("Depth #%d : ELEM_BOX\n", depth);
		for (int j = 0; j < ((t_bvh_elem_box*)root)->n_elems; j++)
		{
			printf("\t%d -> \t", ((t_bvh_elem_box*)root)->elems[j].type);
			print_real3(((t_bvh_elem_box*)root)->elems[j].u.any.coord, "coord: ");
			print_real3(((t_bvh_node *)root)->bbox.beg, "\t\tdeb: ");
			print_real3(((t_bvh_node *)root)->bbox.end, "\t\tend: ");				
		}
	}
}
