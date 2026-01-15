/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:30:31 by fox               #+#    #+#             */
/*   Updated: 2026/01/15 13:20:29 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	get_th_idx(struct s_thread *t)
{
	int				th_idx;

	pthread_mutex_lock(&t->th_idx_mtx);
	th_idx = t->th_idx++;
	pthread_mutex_unlock(&t->th_idx_mtx);
	return (th_idx);
}

static void render_tile(struct s_app *app, int tile_x, int tile_y, 
                        t_color_linear (*rendering)(struct s_app*, t_real, t_real))
{
	const t_int2	r = app->mlx.screen.resolution;
	const t_int2	start = {tile_x, tile_y};
	t_int2			end;
	t_int2			coord;
	
	end = (t_int2){tile_x + TILE_SIDE, tile_y + TILE_SIDE};
	if (end.x > r.x) 
		end.x = r.x;
	if (end.y > r.y) 
		end.y = r.y;
	coord.y = start.y;
	while (coord.y < end.y)
	{
		coord.x = start.x;
		while (coord.x < end.x)
		{
			draw_pixel_to_img(&app->mlx.img, app->mlx.screen.resolution, coord, 
				linear_to_srgb_color(rendering(app, coord.x, coord.y)).value);
			++coord.x;
		}
		++coord.y;
	}
}

__attribute__((const))
static bool	next_tile(int cores, int *x, int *y, t_int2 screen_resolution)
{
	*x = *x + TILE_SIDE * cores;
	while (true)
	{
		if (*x >= screen_resolution.x)
		{
			*x -= screen_resolution.x;
			*y += TILE_SIDE;
			if (*y >= screen_resolution.y)
				return (false);
		}
		else
			return (true);
	}
}

void *render_routine(void *p)
{
	struct s_app	*app;
	t_color_linear	(*rendering)(struct s_app*, t_real, t_real);
	t_int2			coord;
	int				cores;
	int				th_idx;

	app = p;
	cores = app->threads.cpu_cores;
	th_idx = get_th_idx(&app->threads);
	if (app->scene.antialiasing.enabled)
		rendering = antialiasing;
	else
		rendering = basic_render;
	coord.y = 0;
	coord.x = th_idx * TILE_SIDE;
	while (true)
	{
		render_tile(app, coord.x, coord.y, rendering);
		if (!next_tile(cores, &coord.x, &coord.y, app->mlx.screen.resolution))
			break ;
	}
	return (NULL);
}
