/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_tile_downsampled.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:30:57 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/21 14:50:16 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

struct s_downsample
{
	t_int2		r;
	t_int2		start;
	int			rate;
	t_int2		end;
	t_int2		sample_coord;
	t_int2		grid;
	uint32_t	color;
	t_int2		pixel;
};

__attribute__((always_inline))
static inline void	tile_coord(t_app *app, t_int2 tile, struct s_downsample *d)
{
	d->r = app->mlx.screen.resolution;
	d->start.x = tile.x;
	d->start.y = tile.y;
	d->rate = app->render.antialiasing.downsample_rate;
	d->end.x = tile.x + app->render.tile_side;
	d->end.y = tile.y + app->render.tile_side;
	if (d->end.x > d->r.x)
		d->end.x = d->r.x;
	if (d->end.y > d->r.y)
		d->end.y = d->r.y;
}

__attribute__((always_inline))
static inline void	fill_tile(t_app *app, struct s_downsample d)
{
	d.color = linear_to_srgb_color(\
		app->render.antialiasing.rfn(\
			app, d.sample_coord.x, d.sample_coord.y)).value;
	d.grid.y = 0;
	while (d.grid.y < d.rate && d.sample_coord.y + d.grid.y < d.end.y)
	{
		d.grid.x = 0;
		while (d.grid.x < d.rate && d.sample_coord.x + d.grid.x < d.end.x)
		{
			d.pixel.x = d.sample_coord.x + d.grid.x;
			d.pixel.y = d.sample_coord.y + d.grid.y;
			draw_pixel_to_img(&app->mlx.img, d.r, d.pixel, d.color);
			++d.grid.x;
		}
		++d.grid.y;
	}
}

__attribute__((hot))
inline void	render_tile_downsampled(t_app *app, t_int2 tile)
{
	struct s_downsample	d;

	tile_coord(app, tile, &d);
	d.sample_coord.y = d.start.y;
	while (d.sample_coord.y < d.end.y)
	{
		d.sample_coord.x = d.start.x;
		while (d.sample_coord.x < d.end.x)
		{
			fill_tile(app, d);
			d.sample_coord.x += d.rate;
		}
		d.sample_coord.y += d.rate;
	}
}
