/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:27:02 by echatela          #+#    #+#             */
/*   Updated: 2026/01/21 16:37:57 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline void	join_threads(t_thread *t)
{
	int	i;

	i = -1;
	while (++i < t->cpu_cores)
		pthread_join(t->th_tab[i], NULL);
}

int	render(t_app *app)
{
	int	i;

	i = -1;
	while (++i < app->threads.cpu_cores)
	{
		pthread_create(&app->threads.th_tab[i], NULL, render_routine, app);
		if (!app->threads.th_tab[i])
			return (ERR_SYS);
	}
	join_threads(&app->threads);
	app->threads.th_idx = 0;
	mlx_put_image_to_window(app->mlx.mlx, app->mlx.win, app->mlx.img.img, 0, 0);
	return (ERR_NONE);
}

static void	setup_mlx_hooks(t_app *app)
{
	mlx_hook(\
		app->mlx.win, DestroyNotify, ButtonPressMask, event_mouse_close, app);
	mlx_hook(\
		app->mlx.win, MotionNotify, ButtonMotionMask, event_mouse_motion, app);
	mlx_hook(\
		app->mlx.win, ButtonPress, ButtonPressMask, event_mouse_click, app);
	mlx_hook(\
		app->mlx.win, ButtonRelease, ButtonReleaseMask, \
		event_mouse_release, app);
	mlx_hook(\
		app->mlx.win, KeyPress, KeyPressMask, event_keyboard, app);
	mlx_loop_hook(\
		app->mlx.mlx, idle_scroll_reenable, app);
}

int	run_scene(t_app *app)
{
	app->mlx.win = mlx_new_window(app->mlx.mlx, \
			app->mlx.screen.resolution.x, \
			app->mlx.screen.resolution.y, "miniRT");
	setup_mlx_hooks(app);
	render(app);
	mlx_loop(app->mlx.mlx);
	return (0);
}
