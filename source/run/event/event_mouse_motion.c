/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse_motion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:07:09 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/16 21:22:25 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

__attribute__((always_inline))
static inline void	mouse_left_button(struct s_app *app)
{
	const t_real	pan_speed = app->scene.camera.mouse.zoom.pan_speed / ZOOM_TO_PAN_RATIO;
	t_int2			offset;
	
	offset = app->scene.camera.mouse.pos.dir;
	update_cam_dir_xy(&app->scene.camera, 
			(t_real2){-ONE * offset.x * pan_speed, offset.y * pan_speed});
	complete_C(app, &app->scene.camera, false);
}

__attribute__((always_inline))
static inline void	mouse_middle_button(struct s_app *app)
{
	update_camera(&app->scene.camera);
	camera_pan(&app->scene.camera, &app->scene.camera.mouse);
	complete_C(app, &app->scene.camera, false);
}

__attribute__((always_inline))
static inline void	mouse_right_button(struct s_app *app)
{
	bvh_update_coord(app->scene.bvh_root, app->scene.camera.mouse.pos.dir);
	complete_scene(app, &app->scene);
	bound_boxes(app->scene.bvh_root);
}

int	event_mouse_motion(int x, int y, struct s_app *app)
{
	const int		button = app->scene.camera.mouse.button;

	update_mouse_position_nobutton(&app->scene.camera.mouse, x, y);
	if (button == Button1)
		mouse_left_button(app);
	else if (button == Button2)
		mouse_middle_button(app);
	else if (button == Button3)
		mouse_right_button(app);
	render(app);
	return (0);
}
