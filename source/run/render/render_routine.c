/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:20:15 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/21 14:48:28 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

__attribute__((always_inline))
static inline bool
	next_tile(t_app *app, int cores, \
		t_int2 *coord, t_int2 screen_resolution)
{
	coord->x = coord->x + app->render.tile_side * cores;
	while (true)
	{
		if (coord->x >= screen_resolution.x)
		{
			coord->y += app->render.tile_side;
			if (coord->y >= screen_resolution.y)
				return (false);
			coord->x = (int)(coord->x * app->render.inv_tile_side) % cores \
			* app->render.tile_side;
		}
		else
			return (true);
	}
}

__attribute__((always_inline))
inline void	render_tile(t_app *app, t_int2 tile)
{
	const t_int2	r = app->mlx.screen.resolution;
	const t_int2	start = {tile.x, tile.y};
	t_int2			end;
	t_int2			coord;

	end = (t_int2){tile.x + app->render.tile_side, tile.y \
		+ app->render.tile_side};
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
			draw_pixel_to_img(&app->mlx.img, app->mlx.screen.resolution, coord, \
				linear_to_srgb_color(\
					app->render.antialiasing.rfn(app, coord.x, coord.y)).value);
			++coord.x;
		}
		++coord.y;
	}
}

__attribute__((hot))
void	*render_routine(void *p)
{
	t_app	*app;
	t_int2	coord;
	int		cores;
	int		th_idx;

	app = p;
	cores = app->threads.cpu_cores;
	th_idx = app->threads.th_idx++;
	coord.y = 0;
	coord.x = th_idx * app->render.tile_side;
	while (true)
	{
		app->render.antialiasing.tfn(app, coord);
		if (!next_tile(app, cores, &coord, app->mlx.screen.resolution))
			break ;
	}
	return (NULL);
}
