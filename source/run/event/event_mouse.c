/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:32:48 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/20 20:32:02 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	event_mouse_close(struct s_app *app)
{
	mlx_loop_end(app->mlx.mlx);
	return (0);
}

__attribute__((always_inline))
static inline long	get_elapsed_ms(struct timeval start, struct timeval end)
{
	return ((end.tv_sec - start.tv_sec) * 1000
		+ (end.tv_usec - start.tv_usec) / 1000);
}

int	idle_scroll_reenable(void *p)
{
	struct s_app	*app;
	struct timeval	now;
	long			elapsed_ms;

	app = p;
	if (app->scene.camera.mouse.is_scrolling)
	{
		gettimeofday(&now, NULL);
		elapsed_ms = \
			get_elapsed_ms(app->scene.camera.mouse.last_action_time, now);
		if (elapsed_ms >= IDLE_SCROLL_REENABLE_TILE)
		{
			app->scene.camera.mouse.is_scrolling = false;
			app->render.antialiasing.enabled = true;
			app->render.antialiasing.rfn = antialiasing;
			stop_downsampling(&app->render.antialiasing);
			render(app);
		}
	}
	return (0);
}

int	event_mouse_click(int button, int x, int y, struct s_app *app)
{
	t_real		factor;

	update_mouse_position(&app->scene.camera.mouse, button, x, y);
	toggle_antialiasing(&app->render.antialiasing);
	start_downsampling(&app->render.antialiasing);
	if (button == Button4 || button == Button5)
	{
		gettimeofday(&app->scene.camera.mouse.last_action_time, NULL);
		app->scene.camera.mouse.is_scrolling = true;
		if (button == Button5)
			factor = -FLT_1;
		else
			factor = FLT_1;
		camera_zoom(\
			app, &app->scene.camera, factor \
			* app->scene.camera.mouse.pan_speed);
		setup_c(app, &app->scene.camera, false);
	}	
	return (0);
}

int	event_mouse_release(int button, int x, int y, struct s_app *app)
{
	update_mouse_position(&app->scene.camera.mouse, button, x, y);
	if (button == Button1 || button == Button2 || button == Button3)
	{
		toggle_antialiasing(&app->render.antialiasing);
		stop_downsampling(&app->render.antialiasing);
	}
	render(app);
	return (0);
}
