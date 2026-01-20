/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:26:21 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/20 20:33:39 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_sp(struct s_elem *e, int fd)
{
	const struct s_sphere	*sphere = (struct s_sphere *) e;

	dprintf(fd, "sp\t"REAL3"\t"REAL"\t"COLOR_RGB,
		sphere->coord.x,
		sphere->coord.y,
		sphere->coord.z,
		sphere->radius * FLT_2,
		sphere->material.color.s_rgb.r,
		sphere->material.color.s_rgb.g,
		sphere->material.color.s_rgb.b);
}

static void	print_cy(struct s_elem *e, int fd)
{
	const struct s_cylinder	*cylinder = (struct s_cylinder *) e;

	dprintf(fd, "cy\t"REAL3"\t"REAL3"\t""\t"REAL"\t""\t"REAL"\t"COLOR_RGB,
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

static void	print_co(struct s_elem *e, int fd)
{
	const struct s_cone	*cone = (struct s_cone *) e;

	dprintf(fd, "co\t"REAL3"\t"REAL3"\t""\t"REAL"\t""\t"REAL"\t"COLOR_RGB,
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
	static void	(*print_fn[N_SCENE_ELEMS - 1])(struct s_elem *, int) = {
		print_sp, print_cy, print_co};
	int			i;

	i = -1;
	while (++i < e->n_elems)
	{
		print_fn[e->elems[i].type - 1]((struct s_elem *) &e->elems[i], fd);
		print_shape_material(fd, &e->elems[i].u.any.material);
		dprintf(fd, "\n");
	}
}
