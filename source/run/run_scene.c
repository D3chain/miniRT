/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:27:02 by echatela          #+#    #+#             */
/*   Updated: 2026/01/15 16:58:17 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
# include "unistd.h"

static inline void	reset_th_idx(struct s_thread *t)
{
	pthread_mutex_lock(&t->th_idx_mtx);
	t->th_idx = 0;
	pthread_mutex_unlock(&t->th_idx_mtx);
}

static inline void	join_threads(struct s_thread *t)
{
	int	i;

	i = -1;
	while (++i < t->cpu_cores)
		pthread_join(t->th_tab[i], NULL);
}

int	render(struct s_app *app)
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
	reset_th_idx(&app->threads);
	mlx_put_image_to_window(app->mlx.mlx, app->mlx.win, app->mlx.img.img, 0, 0);
	printf("image printed\n");
	return (ERR_NONE);
}

int run_scene(struct s_app *app)
{

	app->mlx.win = mlx_new_window(app->mlx.mlx, app->mlx.screen.resolution.x, app->mlx.screen.resolution.y, "miniRT");
	mlx_hook(app->mlx.win, DestroyNotify, ButtonPressMask, event_mouse_close, app);
	mlx_hook(app->mlx.win, MotionNotify, ButtonMotionMask, event_mouse_motion, app);
	mlx_hook(app->mlx.win, ButtonPress, ButtonPressMask, event_mouse_click, app);
	mlx_hook(app->mlx.win, ButtonRelease, ButtonReleaseMask, event_mouse_release, app);
	mlx_hook(app->mlx.win, KeyPress, KeyPressMask, event_keyboard_press, app);
	
	render(app);
	mlx_loop(app->mlx.mlx);
	return (0);
}

	// mlx_hook(fdf->mlx->win, KeyPress, KeyPressMask, \
	// 											event_keyboard_press, fdf);
	// mlx_hook(fdf->mlx->win, DestroyNotify, ButtonPressMask, \
	// 											event_mouse_close, fdf);
	// mlx_hook(fdf->mlx->win, MotionNotify, ButtonMotionMask, \
	// 											event_mouse_motion, fdf);
	// mlx_hook(fdf->mlx->win, ButtonPress, ButtonPressMask, \
	// 											event_mouse_click, fdf);