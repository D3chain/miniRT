/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:20:08 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/19 22:17:23 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	setup_pl(struct s_app *app, struct s_elem *elem)
{
	struct s_plane	*plane;

	plane = &elem->u.plane;
	plane->normal = normalize3(plane->normal);
	plane->material.color_linear = srgb_to_linear_color(plane->material.color);
}

void	setup_sp(struct s_app *app, struct s_elem *elem)
{
	struct s_sphere	*sphere;

	sphere = &elem->u.sphere;
	sphere->radius_sq = sphere->radius * sphere->radius;
	sphere->material.color_linear = srgb_to_linear_color(sphere->material.color);
}

void	setup_cy(struct s_app *app, struct s_elem *elem)
{
	struct s_cylinder	*cylinder;

	cylinder = &elem->u.cylinder;
	cylinder->axis = normalize3(cylinder->axis);
	cylinder->p1 = project(cylinder->coord, fmul3(cylinder->axis, -1.0), cylinder->height / 2);
	cylinder->p2 = project(cylinder->coord, cylinder->axis, cylinder->height / 2);
	cylinder->radius_sq = cylinder->radius * cylinder->radius;
	cylinder->material.color_linear = srgb_to_linear_color(cylinder->material.color);
}

void	setup_co(struct s_app *app, struct s_elem *elem)
{
	struct s_cone	*cone;
	t_real			cos_theta;

	cone = &elem->u.cone;
	cone->axis = normalize3(cone->axis);
	cone->apex = project(cone->coord, fmul3(cone->axis, -1.0), cone->height / 2);
	cone->base = project(cone->coord, cone->axis, cone->height / 2);
	cone->radius_sq = cone->radius * cone->radius;
	cone->theta = atan(cone->radius / cone->height);
	cos_theta = cos(cone->theta);
	cone->cos2_theta = cos_theta * cos_theta;
	cone->material.color_linear = srgb_to_linear_color(cone->material.color);
}

void	 setup_shapes(struct s_app *app, struct s_scene *scene)
{
	static void	(*setup_fct[N_SCENE_ELEMS])(struct s_app *, struct s_elem *) = {
		setup_pl, setup_sp, setup_cy, setup_co};
	int	i;

	i = -1;
	while (++i < scene->n_elem)
		setup_fct[scene->elems[i].type](app, &scene->elems[i]);
	i = -1;
	while (++i < scene->n_elem_inf)
		setup_fct[scene->elems_inf[i].type](app, &scene->elems_inf[i]);
}
