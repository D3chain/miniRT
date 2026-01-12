/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_elem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:19:17 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/12 16:40:32 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	complete_material(t_material *mat)
{
	mat->ks = COEF_SPEC;
	mat->shininess = SHININESS;
}

void	complete_pl(struct s_app *app, struct s_elem *elem)
{
	struct s_plane	*plane;

	plane = &elem->u.plane;
	plane->normal = normalize3(plane->normal);
	plane->material.color_linear = srgb_to_linear_color(plane->material.color);
	randomize_material(&plane->material);
}

void	complete_sp(struct s_app *app, struct s_elem *elem)
{
	struct s_sphere	*sphere;

	sphere = &elem->u.sphere;
	sphere->radius_sq = sphere->radius * sphere->radius;
	sphere->material.color_linear = srgb_to_linear_color(sphere->material.color);
	randomize_material(&sphere->material);
}

void	complete_cy(struct s_app *app, struct s_elem *elem)
{
	struct s_cylinder	*cylinder;

	cylinder = &elem->u.cylinder;
	cylinder->axis = normalize3(cylinder->axis);
	cylinder->p1 = project(cylinder->coord, mul3(cylinder->axis, -1.0), cylinder->height / 2);
	cylinder->p2 = project(cylinder->coord, cylinder->axis, cylinder->height / 2);
	cylinder->radius_sq = cylinder->radius * cylinder->radius;
	cylinder->material.color_linear = srgb_to_linear_color(cylinder->material.color);
	randomize_material(&cylinder->material);
}

void	complete_co(struct s_app *app, struct s_elem *elem)
{
	struct s_cone	*cone;

	cone = &elem->u.cone;
	cone->axis = normalize3(cone->axis);
	cone->apex = project(cone->coord, mul3(cone->axis, -1.0), cone->height / 2);
	cone->base = project(cone->apex, cone->axis, cone->height / 2);
	cone->radius_sq = cone->radius * cone->radius;
	cone->theta = atan(cone->radius / cone->height);
	cone->cos2_theta = cos(cone->theta) * cos(cone->theta);
	cone->material.color_linear = srgb_to_linear_color(cone->material.color);
	randomize_material(&cone->material);
}

// void	complete_co(struct s_app *app, struct s_elem *elem)
// {
// 	struct s_cone	*cone;

// 	cone = &elem->u.cone;
// 	cone->axis = normalize3(cone->axis);
// 	cone->p1 = project(cone->coord, cone->axis, cone->height / 2);
// 	cone->p2 = project(cone->coord, mul3(cone->axis, -1.0), cone->height / 2);
// 	cone->radius_sq = cone->radius * cone->radius;
// 	cone->material.color_linear = srgb_to_linear_color(cone->material.color);
// 	randomize_material(&cone->material);
// }
