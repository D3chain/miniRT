/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:20:08 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/21 17:27:42 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	setup_pl(t_app *app, t_shape *elem)
{
	t_plane	*plane;

	(void) app;
	plane = &elem->u_.plane;
	plane->normal = normalize3(plane->normal);
	plane->material.color_linear = srgb_to_linear_color(plane->material.color);
}

void	setup_sp(t_app *app, t_shape *elem)
{
	t_sphere	*sphere;

	(void) app;
	sphere = &elem->u_.sphere;
	sphere->radius_sq = sphere->radius * sphere->radius;
	sphere->material.color_linear = \
		srgb_to_linear_color(sphere->material.color);
}

void	setup_cy(t_app *app, t_shape *elem)
{
	t_cylinder	*cylinder;

	(void) app;
	cylinder = &elem->u_.cylinder;
	cylinder->axis = normalize3(cylinder->axis);
	cylinder->p1 = project(cylinder->coord, \
		fmul3(cylinder->axis, -1.0), cylinder->height / 2);
	cylinder->p2 = project(cylinder->coord, \
		cylinder->axis, cylinder->height / 2);
	cylinder->radius_sq = cylinder->radius * cylinder->radius;
	cylinder->material.color_linear = \
		srgb_to_linear_color(cylinder->material.color);
}

void	setup_co(t_app *app, t_shape *elem)
{
	t_cone	*cone;
	t_real	cos_theta;

	(void) app;
	cone = &elem->u_.cone;
	cone->axis = normalize3(cone->axis);
	cone->apex = \
		project(cone->coord, fmul3(cone->axis, -1.0), cone->height / 2);
	cone->base = project(cone->coord, cone->axis, cone->height / 2);
	cone->radius_sq = cone->radius * cone->radius;
	cone->theta = atan(cone->radius / cone->height);
	cos_theta = cos(cone->theta);
	cone->cos2_theta = cos_theta * cos_theta;
	cone->material.color_linear = srgb_to_linear_color(cone->material.color);
}

void	setup_shapes(t_app *app, t_scene *scene)
{
	static t_setup_fn	sfn = {setup_pl, setup_sp, setup_cy, setup_co};
	int					i;

	i = -1;
	while (++i < scene->n_elem)
		sfn[scene->elems[i].type](app, &scene->elems[i]);
	i = -1;
	while (++i < scene->n_elem_inf)
		sfn[scene->elems_inf[i].type](app, &scene->elems_inf[i]);
}
