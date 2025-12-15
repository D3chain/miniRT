/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_elem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:19:17 by cgajean           #+#    #+#             */
/*   Updated: 2025/12/15 16:05:15 by cgajean          ###   ########.fr       */
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
	complete_material(&plane->material);
}

void	complete_sp(struct s_app *app, struct s_elem *elem)
{
	struct s_sphere	*sphere;

	sphere = &elem->u.sphere;
	sphere->radius_sq = sphere->radius * sphere->radius;
	complete_material(&sphere->material);
}

void	complete_cy(struct s_app *app, struct s_elem *elem)
{
	struct s_cylinder	*cylinder;

	cylinder = &elem->u.cylinder;
	cylinder->radius_sq = cylinder->radius * cylinder->radius;
	cylinder->axis = normalize3(cylinder->axis);
	complete_material(&cylinder->material);
}