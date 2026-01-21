/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:26:21 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/21 17:28:05 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_sp(t_shape *e, int fd)
{
	const t_sphere	*sphere = (t_sphere *) e;

	dprintf(fd, "sp\t"REAL","REAL","REAL"\t"REAL"\t"INT","INT","INT,
		sphere->coord.x,
		sphere->coord.y,
		sphere->coord.z,
		sphere->radius * FLT_2,
		sphere->material.color.s_rgb.r,
		sphere->material.color.s_rgb.g,
		sphere->material.color.s_rgb.b);
}

static void	print_cy(t_shape *e, int fd)
{
	const t_cylinder	*cylinder = (t_cylinder *) e;

	dprintf(fd, "cy\t"REAL","REAL","REAL"\t"REAL","REAL","REAL"\t" \
										REAL"\t""\t"REAL"\t"INT","INT","INT,
		cylinder->coord.x,
		cylinder->coord.y,
		cylinder->coord.z,
		cylinder->axis.x,
		cylinder->axis.y,
		cylinder->axis.z,
		cylinder->radius * FLT_2,
		cylinder->height,
		cylinder->material.color.s_rgb.r,
		cylinder->material.color.s_rgb.g,
		cylinder->material.color.s_rgb.b);
}

static void	print_co(t_shape *e, int fd)
{
	const t_cone	*cone = (t_cone *) e;

	dprintf(fd, "co\t"REAL","REAL","REAL"\t"REAL","REAL","REAL"\t""\t"REAL"\t" \
													REAL"\t"INT","INT","INT,
		cone->coord.x,
		cone->coord.y,
		cone->coord.z,
		cone->axis.x,
		cone->axis.y,
		cone->axis.z,
		cone->radius * FLT_2,
		cone->height,
		cone->material.color.s_rgb.r,
		cone->material.color.s_rgb.g,
		cone->material.color.s_rgb.b);
}

void	print_shapes(int fd, t_bvh_elem_box *e)
{
	static void	(*print_fn[N_SCENE_ELEMS - 1])(t_shape *, int) = {
		print_sp, print_cy, print_co};
	int			i;

	i = -1;
	while (++i < e->n_elems)
	{
		print_fn[e->elems[i].type - 1]((t_shape *) &e->elems[i], fd);
		print_shape_material(fd, &e->elems[i].u_.any.material);
		dprintf(fd, "\n");
	}
}
