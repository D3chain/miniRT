/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:03:24 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/16 22:27:54 by cgajean          ###   ########.fr       */
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
	return (
		(end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000
	);
}

int	zoom_aliasing_reenable(void *p)
{
	struct s_app	*app;
	struct timeval	now;
	long			elapsed_ms;
	
	app = p;
	if (app->scene.camera.mouse.is_scrolling)
	{
		gettimeofday(&now, NULL);
		elapsed_ms = get_elapsed_ms(app->scene.camera.mouse.last_action_time, now);
		if (elapsed_ms >= ZOOM_ALIASING_REENABLE_TIME)
		{
			app->scene.camera.mouse.is_scrolling = false;
			app->render.antialiasing.enabled = true;
			render(app);
		}
	}
	return (0);
}

int	event_mouse_click(int button, int x, int y, struct s_app *app)
{
	int		factor;

	update_mouse_position(&app->scene.camera.mouse, button, x, y);
	app->render.antialiasing.enabled = false;
	if (button == Button4 || button == Button5)
	{
		gettimeofday(&app->scene.camera.mouse.last_action_time, NULL);
		app->scene.camera.mouse.is_scrolling = true;
		
		if (button == Button5)
			factor = -1;
		else
			factor = 1;
		camera_zoom(app, &app->scene.camera, factor * app->scene.camera.mouse.zoom.pan_speed);
		complete_C(app, &app->scene.camera, false);
	}	
	return (0);
}

int	event_mouse_release(int button, int x, int y, struct s_app *app)
{
	t_real2	xy_offset;
	
	update_mouse_position(&app->scene.camera.mouse, button, x, y);

	if (button == Button1)
		app->render.antialiasing.enabled = true;

	render(app);
	return (0);
}
