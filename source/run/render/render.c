/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:30:31 by fox               #+#    #+#             */
/*   Updated: 2026/01/14 00:28:54 by fox              ###   ########.fr       */
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
	int		start_x = tile_x;
	int		start_y = tile_y;
	int		end_x = tile_x + TILE_SIDE;
	int		end_y = tile_y + TILE_SIDE;
	t_int2	coord;

	if (end_x > WIN_WIDTH) 
		end_x = WIN_WIDTH;
	if (end_y > WIN_HEIGHT) 
		end_y = WIN_HEIGHT;

	coord.y = start_y;
	while (coord.y < end_y)
	{
		coord.x = start_x;
		while (coord.x < end_x)
		{
			draw_pixel_to_img(&app->mlx.img, coord.x, coord.y, 
				linear_to_srgb_color(rendering(app, coord.x, coord.y)).value);
			++coord.x;
		}
		++coord.y;
	}
}

__attribute__((const))
static bool	next_tile(int cores, int *x, int *y)
{
	*x = *x + TILE_SIDE * cores;
	while (true)
	{
		if (*x >= WIN_WIDTH)
		{
			*x -= WIN_WIDTH;
			*y += TILE_SIDE;
			if (*y >= WIN_HEIGHT)
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
		if (!next_tile(cores, &coord.x, &coord.y))
			break ;
	}
	return (NULL);
}
