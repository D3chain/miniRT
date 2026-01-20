/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_elems.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:20:32 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/20 18:45:43 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_real	get_coord(struct s_elem elem, t_div_axis axis)
{
	if (axis == DIV_ALONG_X)
		return (elem.u.any.coord.x);
	if (axis == DIV_ALONG_Y)
		return (elem.u.any.coord.y);
	return (elem.u.any.coord.z);
}

void	sort_elems(t_bvh_elem_box *cur_box, t_div_axis div_axis)
{
	int				i;
	struct s_elem	tmp_elem;
	t_real			coord_i;
	t_real			coord_i_plus_1;

	i = -1;
	while (++i < cur_box->n_elems - 1)
	{
		coord_i = get_coord(cur_box->elems[i], div_axis);
		coord_i_plus_1 = get_coord(cur_box->elems[i + 1], div_axis);
		if (coord_i > coord_i_plus_1)
		{
			tmp_elem = cur_box->elems[i];
			cur_box->elems[i] = cur_box->elems[i + 1];
			cur_box->elems[i + 1] = tmp_elem;
			i = -1;
		}
	}
}
