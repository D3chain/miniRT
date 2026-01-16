/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:48:52 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/16 22:21:42 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void	update_camera(struct s_camera *camera)
// {
// 	static const t_real3	world_up = (t_real3){ZERO,ONE,ZERO};
// 	static const t_real3	fallback = (t_real3){ZERO,ZERO,ONE};
// 	static const t_real		vlimit = ONE - EPSILON;
// 	const t_real3			cam_dir_norm = camera->dir;
	
// 	if (fabs(dot(cam_dir_norm, world_up)) >  vlimit)
// 		camera->dir_right = normalize3(cross3(cam_dir_norm, fallback));
// 	else
// 		camera->dir_right = normalize3(cross3(cam_dir_norm, world_up));
// 	camera->dir_up = cross3(camera->dir_right, cam_dir_norm);
// }

void	update_camera(struct s_camera *camera)
{
	static const t_real3	world_up = (t_real3){ZERO, ONE, ZERO};
	static const t_real3	fallback = (t_real3){ZERO, ZERO, ONE};
	static const t_real		vlimit = ONE - EPSILON;
	const t_real3			cam_dir_norm = camera->dir;
	t_real3					reference_up;
	
	if (fabs(dot(cam_dir_norm, world_up)) > vlimit)
		reference_up = fallback;
	else
		reference_up = world_up;
	camera->dir_right = normalize3(cross3(cam_dir_norm, reference_up));
	camera->dir_up = cross3(camera->dir_right, cam_dir_norm);
}

void	update_cam_dir_xy(struct s_camera *camera, t_real2 value)
{
	camera->dir.x += value.x;
	camera->dir.y += value.y;
	update_camera(camera);
}

void	camera_zoom(struct s_app *app, struct s_camera *camera, t_real value)
{
	t_ray	zoom_dir;

	if (camera->mouse.button == Button4)
	{
		init_ray(app, &zoom_dir, camera->mouse.pos.cur.x, camera->mouse.pos.cur.y);
		camera->focal_center = plus3(camera->focal_center, fmul3(zoom_dir.dir, value));
	}
	else
		camera->focal_center = plus3(camera->focal_center, fmul3(camera->dir, value));
	
}

void	camera_pan(struct s_camera *camera, struct s_mouse *mouse)
{
	t_real3	offset;
	t_real	factor;
	factor = camera->mouse.zoom.pan_speed;

	offset = fmul3(camera->dir_right, mouse->pos.dir.x * factor);
	camera->focal_center = plus3(camera->focal_center, offset);

	offset = fmul3(camera->dir_up, mouse->pos.dir.y * factor);
	camera->focal_center = plus3(camera->focal_center, offset);
	update_camera(camera);
}
