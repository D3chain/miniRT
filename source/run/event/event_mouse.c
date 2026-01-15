/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:03:24 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/15 17:29:27 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	event_mouse_close(struct s_app *app)
{
	mlx_loop_end(app->mlx.mlx);
	return (0);
}

int	event_mouse_click(int button, int x, int y, struct s_app *app)
{
	update_mouse(&app->render.mouse, button, x, y);
	app->scene.antialiasing.enabled = false;
	return (0);
}

int	event_mouse_release(int button, int x, int y, struct s_app *app)
{
	t_real2	xy_offset;
	int		factor;
	
	update_mouse(&app->render.mouse, button, x, y);
	if (app->scene.camera.move_what == MOVE_OBJETCS && button == Button1)
	{
		bvh_update_coord(app->scene.bvh_root, app->render.mouse.dir);
		complete_scene(app, &app->scene);
		bound_boxes(app->scene.bvh_root);
	}
	else if (app->scene.camera.move_what == MOVE_CAMERA_ANGLE && button == Button1)
	{
		xy_offset.x = (app->render.mouse.pos_prv.x - app->render.mouse.pos_cur.x) * app->scene.camera.pan_speed / 10; 
		xy_offset.y = (app->render.mouse.pos_cur.y - app->render.mouse.pos_prv.y) * app->scene.camera.pan_speed / 10;
		update_cam_dir_xy(&app->scene.camera, xy_offset);
		complete_C(app, &app->scene.camera, false);
	}
	else if (button == Button4 || button == Button5)
	{
		if (button == Button5)
			factor = -1;
		else
			factor = 1;
		update_camera_z(&app->scene.camera, factor * app->scene.camera.pan_speed);
		complete_C(app, &app->scene.camera, false);
	}
	app->scene.antialiasing.enabled = true;
	render(app);
	return (0);
}
