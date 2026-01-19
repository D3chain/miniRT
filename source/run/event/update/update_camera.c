/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:48:52 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/19 16:24:24 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

struct s_rodrigues
{
	t_real	cos_a;
	t_real	sin_a;
	t_real	dot_va;
	t_real3	cross_av;
	t_real3	term1;
	t_real3	term2;
	t_real3	term3;
};

void	update_camera(struct s_app *app, struct s_camera *camera)
{
	static const t_real3	world_up = (t_real3){FLT_0,FLT_1,FLT_0};
	static const t_real3	fallback = (t_real3){FLT_0,FLT_0,FLT_1};
	static const t_real		vlimit = FLT_1 - EPSILON;
	const t_real3			cam_dir_norm = camera->dir;
	
	if (fabs(dot(cam_dir_norm, world_up)) >  vlimit)
		camera->dir_right = normalize3(cross3(cam_dir_norm, fallback));
	else
		camera->dir_right = normalize3(cross3(cam_dir_norm, world_up));
	camera->dir_up = cross3(camera->dir_right, cam_dir_norm);
	app->scene.camera.fov_rad = ft_toradian(app->scene.camera.fov);
	setup_viewport(app, &app->scene.camera);	
}

//	Rotation around an arbitrary axis (Rodrigues's rotation formula)
//	https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula
__attribute__((always_inline))
static inline t_real3	rotate_around_axis(t_real3 vec, t_real3 axis, t_real angle)
{
	struct s_rodrigues	r;

	r.cos_a = cos(angle);
	r.sin_a = sin(angle);
	r.dot_va = dot(vec, axis);
	r.cross_av = cross3(axis, vec);
	r.term1 = fmul3(vec, r.cos_a);
	r.term2 = fmul3(r.cross_av, r.sin_a);
	r.term3 = fmul3(axis, r.dot_va * (FLT_1 - r.cos_a));
	return (plus3(r.term1, plus3(r.term2, r.term3)));
}

void camera_view(struct s_app *app, struct s_camera *camera, t_real2 delta_pixels)
{
	t_real3 new_dir;

	new_dir = rotate_around_axis(camera->dir, camera->dir_up, -delta_pixels.x * MOUSE_SENSITIVITY);
	new_dir = rotate_around_axis(new_dir, camera->dir_right, delta_pixels.y * MOUSE_SENSITIVITY);
	camera->dir = normalize3(new_dir);
	update_camera(app, camera);
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

void	camera_pan(struct s_app *app, struct s_camera *camera, struct s_mouse *mouse)
{
	const t_real	factor = camera->mouse.pan_speed * ZOOM_MIN_SPEED;
	t_real3			offset;

	offset = fmul3(camera->dir_right, mouse->pos.dir.x * factor);
	camera->focal_center = plus3(camera->focal_center, offset);

	offset = fmul3(camera->dir_up, mouse->pos.dir.y * factor);
	camera->focal_center = plus3(camera->focal_center, offset);
	update_camera(app, camera);
}
