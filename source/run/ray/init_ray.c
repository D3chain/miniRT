/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:25:22 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/21 12:14:45 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

__attribute__((always_inline))
void	init_ray(t_app *app, t_ray *ray, t_real x, t_real y)
{
	const t_real3	delta = plus3(fmul3(app->scene.camera.wp.u_px, \
		(t_real)x), fmul3(app->scene.camera.wp.v_px, (t_real)y));
	const t_real3	px_pos = plus3(app->scene.camera.wp.pixel00_loc, delta);

	ray->dir = normalize3(minus3(px_pos, app->scene.camera.focal_center));
	ray->origin = app->scene.camera.focal_center;
}
