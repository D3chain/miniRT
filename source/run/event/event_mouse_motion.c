/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse_motion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:07:09 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/21 11:45:24 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

__attribute__((always_inline))
static inline void	mouse_left_button(t_app *app)
{
	t_int2			offset;

	offset = app->scene.camera.mouse.pos.dir;
	camera_view(app, &app->scene.camera, \
			(t_real2){offset.x * CAMERA_VIEW_FACTOR, \
				offset.y * CAMERA_VIEW_FACTOR});
}

__attribute__((always_inline))
static inline void	mouse_middle_button(t_app *app)
{
	camera_pan(app, &app->scene.camera, &app->scene.camera.mouse);
}

__attribute__((always_inline))
static inline void	mouse_right_button(t_app *app)
{
	update_shapes_coord(\
		&app->scene.camera, app->scene.bvh_root, \
		app->scene.camera.mouse.pos.dir);
	setup_shapes(app, &app->scene);
	bound_boxes(app->scene.bvh_root);
}

int	event_mouse_motion(int x, int y, t_app *app)
{
	const int		button = app->scene.camera.mouse.button;

	update_mouse_position_nobutton(&app->scene.camera.mouse, x, y);
	start_downsampling(&app->render.antialiasing);
	if (button == Button1)
		mouse_left_button(app);
	else if (button == Button2)
		mouse_middle_button(app);
	else if (button == Button3)
		mouse_right_button(app);
	render(app);
	return (0);
}
