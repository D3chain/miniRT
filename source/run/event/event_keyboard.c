/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_keyboard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:20:04 by echatela          #+#    #+#             */
/*   Updated: 2026/01/21 11:45:24 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline void	fov_modify(t_app *app, int key)
{
	static const t_real	min_fov = FOV_MIN;
	static const t_real	max_fov = FOV_MAX;
	t_real				new_fov;

	if (key == XK_KP_Add)
	{
		new_fov = app->scene.camera.fov + FOV_MODIFY;
		if (new_fov > max_fov)
			app->scene.camera.fov = max_fov;
		else
			app->scene.camera.fov = new_fov;
	}
	else
	{
		new_fov = app->scene.camera.fov - FOV_MODIFY;
		if (new_fov < min_fov)
			app->scene.camera.fov = min_fov;
		else
			app->scene.camera.fov = new_fov;
	}
	printf("FOV=%.0f\n", app->scene.camera.fov);
	update_camera(app, &app->scene.camera);
	render(app);
}

int	event_keyboard_press(int key, t_app *app)
{
	if (key == XK_Escape)
		mlx_loop_end(app->mlx.mlx);
	else if (key == XK_a || key == XK_z || key == XK_e)
		update_antialiasing(key, app);
	else if (key == XK_c)
		print_camera(app);
	else if (key == XK_r)
		print_render(app);
	else if (key == XK_m)
		print_map(app);
	else if (key == XK_equal || key == XK_minus || key == XK_BackSpace)
		update_zoom_speed(key, app);
	else if (key == XK_KP_Add || key == XK_KP_Subtract)
		fov_modify(app, key);
	else if (key == XK_t)
		print_bvh_tree(app->scene.bvh_root);
	else if (key == XK_d)
		toggle_downsampling(&app->render.antialiasing);
	else if (key == XK_Page_Up)
		increase_downsampling(&app->render.antialiasing);
	else if (key == XK_Page_Down)
		decrease_downsampling(&app->render.antialiasing);
	return (0);
}
