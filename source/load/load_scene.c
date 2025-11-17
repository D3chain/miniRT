/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:51:21 by echatela          #+#    #+#             */
/*   Updated: 2025/11/17 16:11:41 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define RED 0xFFFF

struct s_elem	create_sphere(t_double3 coord, double diametre, t_rgb color)
{
	struct s_elem	sphere;

	sphere.type = SPHERE;
	sphere.u.sphere.coord = coord;
	sphere.u.sphere.diametre = diametre;
	sphere.u.sphere.color = color;
	return (sphere);
}

int	load_scene(struct s_app *app, char *file)
{
	(void) file;
	app->scene.elems = xmalloc(app, sizeof(struct s_elem) * 1);
	app->scene.elems[0] = create_sphere((t_double3){0.0, 0.0, 0.0}, 5, color_int(RED));
	return (app->status);
}
