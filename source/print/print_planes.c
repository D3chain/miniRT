/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_planes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 17:43:34 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/21 17:43:49 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_pl(t_shape *e, int fd)
{
	const t_plane	*plane = (t_plane *) e;

	dprintf(fd, "pl\t"REAL","REAL","REAL"\t"REAL","REAL","REAL"\t"INT","INT","INT,
		plane->coord.x,
		plane->coord.y,
		plane->coord.z,
		plane->normal.x,
		plane->normal.y,
		plane->normal.z,
		plane->material.color.s_rgb.r,
		plane->material.color.s_rgb.g,
		plane->material.color.s_rgb.b);
}

void	print_planes(int fd, t_scene *scene)
{
	int			i;

	i = -1;
	while (++i < scene->n_elem_inf)
	{
		print_pl(&scene->elems_inf[i], fd);
		print_shape_material(fd, &scene->elems_inf[i].u_.any.material);
		dprintf(fd, "\n");
	}
	dprintf(fd, "\n");
}
