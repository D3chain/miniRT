/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_keyboard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:20:04 by echatela          #+#    #+#             */
/*   Updated: 2026/01/15 17:27:00 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline void	zoom_speed(int key, struct s_app *app)
{
	static const t_real	zoom_speed[2] = {ZOOM_BASE_PAN_SPEED, ZOOM_FAST_PAN_SPEED};
	static const char	*state[] = {"OFF", "ON"};
	bool				fast_zoom;
	
	if (key == XK_equal)
		app->scene.camera.base_pan_speed += 0.1f;
	else if (key == XK_minus)
	{
		if (app->scene.camera.base_pan_speed - 0.1f > 0.1f)
			app->scene.camera.base_pan_speed -= 0.1f;
		else
			return ;
	}
	else if (key == XK_BackSpace)
	{
		fast_zoom = !app->scene.camera.fast_zoom;
		app->scene.camera.fast_zoom = fast_zoom;
		app->scene.camera.base_pan_speed = zoom_speed[fast_zoom];
		app->scene.camera.pan_speed = app->scene.camera.base_pan_speed * app->scene.camera.pan_fov_ratio;
		printf("Fast zoom is %s\n", state[fast_zoom]);
	}
	app->scene.camera.pan_speed = app->scene.camera.base_pan_speed * app->scene.camera.pan_fov_ratio;
	printf("Zoom speed: %.1f\n", app->scene.camera.pan_speed);
}



int	event_keyboard_press(int key, struct s_app *app)
{
	static const char	*move[] = {"OBJECTS", "CAMERA_ANGLE", "CAMERA_POS"};
	static const char	*mid[] = {"ZOOM", "TILT_Z"};
	
	if (key == XK_Escape)
		mlx_loop_end(app->mlx.mlx);
	else if (key == XK_a)
	{
		app->scene.antialiasing.enabled = !app->scene.antialiasing.enabled;
		printf("Antialiasing=%d\n", app->scene.antialiasing.enabled);
		if (app->scene.antialiasing.enabled)
			printf("Oversampling=%d\n", app->scene.antialiasing.oversampling);
		render(app);
	}
	else if (key == XK_z)
	{
		if (app->scene.antialiasing.enabled == false)
		{
			app->scene.antialiasing.enabled = true;
			printf("Oversampling has been enabled\n");
		}
		++app->scene.antialiasing.grid_size;
		app->scene.antialiasing.oversampling = pow(app->scene.antialiasing.grid_size, 2.0);
		printf("Oversampling=%d\n", app->scene.antialiasing.oversampling);
		render(app);
	}
	else if (key == XK_e)
	{
		if (app->scene.antialiasing.grid_size == 2)
		{
			app->scene.antialiasing.enabled = false;
			app->scene.antialiasing.grid_size = 1;
			printf("Oversampling has been disabled.\n");
			render(app);
		}
		else if (app->scene.antialiasing.grid_size > 2)
		{
			--app->scene.antialiasing.grid_size;
			app->scene.antialiasing.oversampling = pow(app->scene.antialiasing.grid_size, 2.0);
			printf("Oversampling=%d\n", app->scene.antialiasing.oversampling);
			render(app);
		}
		else
			printf("Oversampling is already disabled.\n");
	}
	else if (key == XK_c)
	{
		if (++app->scene.camera.move_what == N_MOVE_OPTIONS)
			app->scene.camera.move_what = 0;
		printf("Move %s\n", move[app->scene.camera.move_what]);
	}
	else if (key == XK_m)
	{
		app->scene.camera.mid_button_what = !app->scene.camera.mid_button_what;
		printf("Mouse MID-button now controls %s\n", mid[app->scene.camera.mid_button_what]);
	}
	else if (key == XK_equal || key == XK_minus || key == XK_BackSpace)
		zoom_speed(key, app);
		
	return (0);
}
