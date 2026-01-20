/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_viewport.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:20:03 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/20 20:14:08 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	setup_viewport(struct s_app *app, struct s_camera *camera)
{
	static const t_real	dir_ceil = FLT_1 - FLT_0_1 / FLT_10;

	camera->wp.height = \
		FLT_2 * tan(camera->fov_rad / FLT_2) * camera->focal_length;
	camera->wp.width = \
		camera->wp.height * app->mlx.screen.img_ratio;
	if (camera->dir.y > dir_ceil || camera->dir.y < -dir_ceil)
		camera->wp.u = (t_real3){FLT_1, FLT_0, FLT_0};
	else
		camera->wp.u = \
			fmul3(normalize3(\
				cross3(camera->dir, \
					(t_real3){FLT_0, -FLT_1, FLT_0})), camera->wp.width);
	camera->wp.u_px = fmul3(camera->wp.u, FLT_1 / app->mlx.screen.resolution.x);
	camera->wp.v = \
		fmul3(normalize3(\
			cross3(camera->dir, camera->wp.u)), -camera->wp.height);
	camera->wp.v_px = fmul3(camera->wp.v, FLT_1 / app->mlx.screen.resolution.y);
	camera->wp.upper_left = \
		minus3(plus3(camera->focal_center, camera->dir), \
			plus3(fmul3(camera->wp.u, FLT_0_5), fmul3(camera->wp.v, FLT_0_5)));
	camera->wp.pixel00_loc = \
		plus3(plus3(camera->wp.upper_left, fmul3(camera->wp.u_px, FLT_0_5)),
			fmul3(camera->wp.v_px, FLT_0_5));
}
