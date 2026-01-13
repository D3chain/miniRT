/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:11:06 by fox               #+#    #+#             */
/*   Updated: 2026/01/13 16:48:26 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

inline void	init_ray(struct s_app *app, struct s_ray *ray, t_real x, t_real y)
{
	const t_real3	delta = plus3(mul3(app->scene.camera.viewport_u_px, (t_real)x), mul3(app->scene.camera.viewport_v_px, (t_real)y));
	const t_real3	px_pos = plus3(app->scene.camera.pixel00_loc, delta);

	ray->dir = normalize3(minus3(px_pos, app->scene.camera.focal_center));
	ray->origin = app->scene.camera.focal_center;
}

