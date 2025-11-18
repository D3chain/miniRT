/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:51:21 by echatela          #+#    #+#             */
/*   Updated: 2025/11/18 10:43:26 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define RED 0x0000FFFF

struct s_elem	create_sphere(t_double3 coord, double diametre, t_color color)
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
	app->scene.camera.coord = (t_double3){0.0, 0.0, -70.0};
	app->scene.camera.dir = (t_double3){0.0, 0.0, 1.0};
	app->scene.camera.fov = 70;
	app->scene.elems = xmalloc(app, sizeof(struct s_elem) * 1);
	app->scene.elems[0] = create_sphere((t_double3){0.0, 0.0, 0.0}, 200, color_int(RED));
	return (app->status);
}
