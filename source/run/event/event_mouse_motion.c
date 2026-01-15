/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse_motion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:07:09 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/15 17:55:58 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	mouse_left_button(struct s_app *app, t_int2 dir)
{
	if (dir.x > 0)
		;
	if (dir.x < 0)
		;
	if (dir.y > 0)
		;
	if (dir.y < 0)
		;
}

static void	mouse_right_button(struct s_app *app, t_int2 dir)
{
	if (dir.x > 0)
		;
	if (dir.x < 0)
		;
	if (dir.y > 0)
		;
	if (dir.y < 0)
		;
}

static void	mouse_middle_button(struct s_app *app, t_int2 dir)
{
	if (dir.x > 0)
		;
	if (dir.x < 0)
		;
	if (dir.y > 0)
		;
	if (dir.y < 0)
		;
}

int	event_mouse_motion(int x, int y, struct s_app *app)
{
	t_real2	xy_offset;
	int		factor;

	update_mouse_nobutton(&app->render.mouse, x, y);

	if (app->scene.camera.move_what == MOVE_OBJETCS && app->render.mouse.button == Button1)
	{
		bvh_update_coord(app->scene.bvh_root, app->render.mouse.dir);
		complete_scene(app, &app->scene);
		bound_boxes(app->scene.bvh_root);
	}
	else if (app->scene.camera.move_what == MOVE_CAMERA_ANGLE && app->render.mouse.button == Button1)
	{
		xy_offset.x = (app->render.mouse.pos_prv.x - app->render.mouse.pos_cur.x) * app->scene.camera.pan_speed / 10; 
		xy_offset.y = (app->render.mouse.pos_cur.y - app->render.mouse.pos_prv.y) * app->scene.camera.pan_speed / 10;
		update_cam_dir_xy(&app->scene.camera, xy_offset);
		complete_C(app, &app->scene.camera, false);
	}
	else if (app->scene.camera.move_what == MOVE_CAMERA_POS && app->render.mouse.button == Button1)
	{
		xy_offset.x = (app->render.mouse.pos_prv.x - app->render.mouse.pos_cur.x) * app->scene.camera.pan_speed / 10; 
		xy_offset.y = (app->render.mouse.pos_cur.y - app->render.mouse.pos_prv.y) * app->scene.camera.pan_speed / 10;
		update_cam_pos_xy(&app->scene.camera, xy_offset);
		complete_C(app, &app->scene.camera, false);
	}	
	else if (app->scene.camera.mid_button_what == MID_ZOOM && app->render.mouse.button == Button2)
	{
		if (app->render.mouse.dir.y > 0)
			factor = -1;
		else
			factor = 1;
		update_camera_z(&app->scene.camera, factor * app->scene.camera.pan_speed);
		complete_C(app, &app->scene.camera, false);
	}
		
	render(app);

	return (0);
}


// Simplifier le traitement de l'image lorsqu'on est en deplacement en adaptant Phong