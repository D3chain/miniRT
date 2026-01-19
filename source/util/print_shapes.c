/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:26:21 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/19 15:28:31 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_sp(struct s_elem *e, int fd)
{
	struct s_sphere	*sphere = (struct s_sphere *) e;
	
	dprintf(fd, "sp\t"REAL3"\t"REAL"\t"COLOR_RGB"\n",
		e->u.sphere.coord.x,
		e->u.sphere.coord.y,
		e->u.sphere.coord.z,
		e->u.sphere.radius * FLT_2,
		e->u.sphere.material.color.s_rgb.r,
		e->u.sphere.material.color.s_rgb.g,
		e->u.sphere.material.color.s_rgb.b
	);
}

static void	print_cy(struct s_elem *e, int fd)
{
	struct s_cylinder	*cylinder = (struct s_cylinder *) e;
	
	dprintf(fd, "cy\t"REAL3"\t"REAL3"\t""\t"REAL"\t""\t"REAL"\t"COLOR_RGB"\n",
		e->u.cylinder.coord.x,
		e->u.cylinder.coord.y,
		e->u.cylinder.coord.z,		
		e->u.cylinder.axis.x,
		e->u.cylinder.axis.y,
		e->u.cylinder.axis.z,
		e->u.cylinder.radius * FLT_2,
		e->u.cylinder.height,
		e->u.cylinder.material.color.s_rgb.r,
		e->u.cylinder.material.color.s_rgb.g,
		e->u.cylinder.material.color.s_rgb.b
	);
}

static void	print_co(struct s_elem *e, int fd)
{
	struct s_cone	*cone = (struct s_cone *) e;
	
	dprintf(fd, "co\t"REAL3"\t"REAL3"\t""\t"REAL"\t""\t"REAL"\t"COLOR_RGB"\n",
		e->u.cone.coord.x,
		e->u.cone.coord.y,
		e->u.cone.coord.z,		
		e->u.cone.axis.x,
		e->u.cone.axis.y,
		e->u.cone.axis.z,
		e->u.cone.radius * FLT_2,
		e->u.cone.height,
		e->u.cone.material.color.s_rgb.r,
		e->u.cone.material.color.s_rgb.g,
		e->u.cone.material.color.s_rgb.b
	);
}

void	print_shapes(int fd, t_bvh_elem_box *e)
{
	static void	(*print_fn[N_SCENE_ELEMS - 1])(struct s_elem *, int) = {
		print_sp, print_cy, print_co};
	int			i;

	i = -1;
	while (++i < e->n_elems)
		print_fn[e->elems[i].type - 1]((struct s_elem *) &e->elems[i], fd);
}
