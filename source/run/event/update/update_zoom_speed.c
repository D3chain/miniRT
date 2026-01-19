/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_zoom_speed.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:24:49 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/19 16:24:52 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	update_zoom_speed(int key, struct s_app *app)
{
	static const t_real		zoom_speed[2] = {ZOOM_BASE_PAN_SPEED, ZOOM_FAST_PAN_SPEED};
	static const char		*state[] = {"OFF", "ON"};
	bool					fast_move;

	if (key == XK_equal)
		app->scene.camera.mouse.base_pan_speed *= ZOOM_INCREASE_FACTOR;
	else if (key == XK_minus)
	{
		if (app->scene.camera.mouse.base_pan_speed * ZOOM_DECREASE_FACTOR > ZOOM_MIN_SPEED)
			app->scene.camera.mouse.base_pan_speed *= ZOOM_DECREASE_FACTOR;
		else
			return ;
	}
	else if (key == XK_BackSpace)
	{
		fast_move = !app->scene.camera.mouse.fast_move;
		app->scene.camera.mouse.fast_move = fast_move;
		app->scene.camera.mouse.base_pan_speed = zoom_speed[fast_move];
		app->scene.camera.mouse.pan_speed = app->scene.camera.mouse.base_pan_speed * app->scene.camera.pan_fov_ratio;
		printf("Fast zoom is %s\n", state[fast_move]);
	}
	app->scene.camera.mouse.pan_speed = app->scene.camera.mouse.base_pan_speed * app->scene.camera.pan_fov_ratio;
	printf("Zoom speed: %.1f\n", app->scene.camera.mouse.pan_speed);
}
