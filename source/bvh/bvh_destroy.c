/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 17:02:40 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/20 17:22:19 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	bvh_destroy(t_bvh_base *root)
{
	if (!root)
		return ;
	if (root->type == NODE_BOX)
	{
		bvh_destroy((t_bvh_base *)((t_bvh_node *)root)->left);
		bvh_destroy((t_bvh_base *)((t_bvh_node *)root)->right);
	}
	free(root);
}
