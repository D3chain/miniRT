/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_shapes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:19:17 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/16 17:18:06 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	complete_material(t_material *mat)
{	
	// il faudra parser les materiaux
	
	mat->ka = 0.1;
	mat->kd = 0.7;
	mat->ks = COEF_SPEC;
		
	mat->shininess = SHININESS;
	mat->ior = 1.5;

	mat->kr = 0.7;
	mat->kt = 0.7;
}

void	complete_pl(struct s_app *app, struct s_elem *elem)
{
	struct s_plane	*plane;

	plane = &elem->u.plane;
	plane->normal = normalize3(plane->normal);
	plane->material.color_linear = srgb_to_linear_color(plane->material.color);
	complete_material(&plane->material);
}

void	complete_sp(struct s_app *app, struct s_elem *elem)
{
	struct s_sphere	*sphere;

	sphere = &elem->u.sphere;
	sphere->radius_sq = sphere->radius * sphere->radius;
	sphere->material.color_linear = srgb_to_linear_color(sphere->material.color);
	complete_material(&sphere->material);
}

void	complete_cy(struct s_app *app, struct s_elem *elem)
{
	struct s_cylinder	*cylinder;

	cylinder = &elem->u.cylinder;
	cylinder->axis = normalize3(cylinder->axis);
	cylinder->p1 = project(cylinder->coord, fmul3(cylinder->axis, -1.0), cylinder->height / 2);
	cylinder->p2 = project(cylinder->coord, cylinder->axis, cylinder->height / 2);
	cylinder->radius_sq = cylinder->radius * cylinder->radius;
	cylinder->material.color_linear = srgb_to_linear_color(cylinder->material.color);
	complete_material(&cylinder->material);
}

void	complete_co(struct s_app *app, struct s_elem *elem)
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
	complete_material(&cone->material);
}
