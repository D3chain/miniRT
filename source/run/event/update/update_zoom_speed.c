/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_zoom_speed.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:24:49 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/20 19:50:24 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#ifdef USE_DBL_NUMBER
# define FLT_PRECISION	"%0.1lf"
#else
# define FLT_PRECISION	"%0.1f"
#endif

static void	equal_key_pressed(struct s_app *app)
{
	app->scene.camera.mouse.base_pan_speed *= ZOOM_INCREASE_FACTOR;
}

static void	backspace_key_pressed(struct s_app *app)
{
	static t_real		speed[2] = {ZOOM_BASE_PAN_SPEED, ZOOM_FAST_PAN_SPEED};
	static const char	*state[] = {"OFF", "ON"};
	bool				fast_move;

	fast_move = !app->scene.camera.mouse.fast_move;
	app->scene.camera.mouse.fast_move = fast_move;
	app->scene.camera.mouse.base_pan_speed = speed[fast_move];
	app->scene.camera.mouse.pan_speed = \
		app->scene.camera.mouse.base_pan_speed \
		* app->scene.camera.pan_fov_ratio;
	printf("Fast zoom is %s\n", state[fast_move]);
}

static void	minus_key_pressed(struct s_app *app)
{
	if (app->scene.camera.mouse.base_pan_speed * ZOOM_DECREASE_FACTOR \
			> ZOOM_MIN_SPEED)
		app->scene.camera.mouse.base_pan_speed *= ZOOM_DECREASE_FACTOR;
}

void	update_zoom_speed(int key, struct s_app *app)
{
	if (key == XK_equal)
		equal_key_pressed(app);
	else if (key == XK_minus)
		return (minus_key_pressed(app));
	else if (key == XK_BackSpace)
		backspace_key_pressed(app);
	app->scene.camera.mouse.pan_speed = \
		app->scene.camera.mouse.base_pan_speed \
		* app->scene.camera.pan_fov_ratio;
	printf("Zoom speed: "FLT_PRECISION"\n", app->scene.camera.mouse.pan_speed);
}
