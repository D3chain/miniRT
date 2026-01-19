/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bvh_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:21:01 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/19 16:21:02 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_bvh_tree_rec(t_bvh_base *root, int depth);

static void	print_bvh_banner(void)
{
	printf("\n");
	printf("╔═════════════════════════════════════════════════════╗\n");
	printf("║            BOUNDING VOLUME HIERARCHY (BVH)          ║\n");
	printf("╚═════════════════════════════════════════════════════╝\n");
}

static void	print_node_box(t_bvh_node *node, int depth)
{
	static const char	*node_type[] = {"ELEM_BOX", "NODE_BOX"};

	printf("\n  Depth #%d : NODE_BOX\n", depth);
	printf("\t       │\n");
	printf("%s : %s\n", "\t       └── Left", node_type[ELEM_BOX]);
	print_real3(node->left->bbox.beg, "\t\t\t    deb: ");
	print_real3(node->left->bbox.end, "\t\t\t    end: ");
	printf("\t       │\n");
	printf("%s : %s\n", "\t       └── Right", node_type[ELEM_BOX]);
	print_real3(node->right->bbox.beg, "\t\t\t    deb: ");
	print_real3(node->right->bbox.end, "\t\t\t    end: ");
	print_bvh_tree_rec(node->left, depth + 1);
	print_bvh_tree_rec(node->right, depth + 1);
}

static void	print_elem_box(t_bvh_elem_box *elem_box, int depth)
{
	int	i;

	printf("\n  Depth #%d : ELEM_BOX\n", depth);
	i = 0;
	while (i < elem_box->n_elems)
	{
		printf("\t       │\n");
		printf("\t       └── elem #%d  ", elem_box->elems[i].type);
		print_real3(elem_box->elems[i].u.any.coord, "coord: ");
		print_real3(elem_box->bbox.beg, "\t\t\t    deb: ");
		print_real3(elem_box->bbox.end, "\t\t\t    end: ");
		i++;
	}
}

void	print_bvh_tree_rec(t_bvh_base *root, int depth)
{
	if (root->type == NODE_BOX)
		print_node_box((t_bvh_node *)root, depth);
	else
		print_elem_box((t_bvh_elem_box *)root, depth);
}

void	print_bvh_tree(t_bvh_base *root)
{
	print_bvh_banner();
	print_bvh_tree_rec(root, 0);
	printf("\n\n");
}
