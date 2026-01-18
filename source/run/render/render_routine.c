/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:30:31 by fox               #+#    #+#             */
/*   Updated: 2026/01/18 20:48:10 by fox              ###   ########.fr       */
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

static bool	next_tile(struct s_app *app, int cores, t_int2 *coord, t_int2 screen_resolution)
{
	coord->x = coord->x + app->render.tile_side * cores;
	while (true)
	{
		if (coord->x >= screen_resolution.x)
		{
			coord->y += app->render.tile_side;
			if (coord->y >= screen_resolution.y)
				return (false);
			coord->x = (int)(coord->x * app->render.inv_tile_side) % cores * app->render.tile_side;
		}
		else
			return (true);
	}
}

__attribute__((always_inline))
inline void	render_tile_downsampled(struct s_app *app, t_int2 tile, render_fn rend)
{
	const t_int2	r = app->mlx.screen.resolution;
	const t_int2	start = {tile.x, tile.y};
	t_int2			end;
	t_int2			coord;
	uint32_t		color_value;
	
	end = (t_int2){tile.x + app->render.tile_side, tile.y + app->render.tile_side};
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
			if (!(coord.x % app->render.antialiasing.downsample_rate) || !(coord.y % app->render.antialiasing.downsample_rate))
				color_value = linear_to_srgb_color(rend(app, coord.x, coord.y)).value;
			draw_pixel_to_img(&app->mlx.img, app->mlx.screen.resolution, coord, color_value);
			++coord.x;
		}
		++coord.y;
	}
}

__attribute__((always_inline))
inline void	render_tile(struct s_app *app, t_int2 tile, render_fn rend)
{
	const t_int2	r = app->mlx.screen.resolution;
	const t_int2	start = {tile.x, tile.y};
	t_int2			end;
	t_int2			coord;
	
	end = (t_int2){tile.x + app->render.tile_side, tile.y + app->render.tile_side};
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
				linear_to_srgb_color(rend(app, coord.x, coord.y)).value);
			++coord.x;
		}
		++coord.y;
	}
}

void *render_routine(void *p)
{
	struct s_app	*app;
	t_int2			coord;
	int				cores;
	int				th_idx;

	app = p;
	cores = app->threads.cpu_cores;
	th_idx = get_th_idx(&app->threads);

	coord.y = 0;
	coord.x = th_idx * app->render.tile_side;
	while (true)
	{
		app->render.antialiasing.tfn(app, coord, app->render.antialiasing.rfn);
		if (!next_tile(app, cores, &coord, app->mlx.screen.resolution))
			break ;
	}
	return (NULL);
}
