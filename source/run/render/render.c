/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:30:31 by fox               #+#    #+#             */
/*   Updated: 2026/01/13 16:28:47 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void render(struct s_app *app)
// {
// 	double			x;
// 	double			y;
// 	t_color_linear	(*rendering)(struct s_app*, double, double);
// 	t_color_linear	final_color_linear;

// 	if (app->scene.antialiasing.enabled)
// 		rendering = antialiasing;
// 	else
// 		rendering = basic_render;

// 	x = 0.0;
// 	while (x++ < WIN_WIDTH)
// 	{
// 		y = 0.0;
// 		while (y++ < WIN_HEIGHT)
// 			draw_pixel_to_img(&app->mlx.img, x, y, 
// 				linear_to_srgb_color(rendering(app, x, y)).value);
// 	}
// 	mlx_put_image_to_window(app->mlx.mlx, app->mlx.win, app->mlx.img.img, 0, 0);
// 	printf("image printed\n");
// }


static int	get_th_idx(struct s_thread *t)
{
	int				th_idx;

	pthread_mutex_lock(&t->th_idx_mtx);
	th_idx = t->th_idx++;
	pthread_mutex_unlock(&t->th_idx_mtx);
	return (th_idx);
}

static void render_tile(struct s_app *app, int tile_x, int tile_y, 
                        t_color_linear (*rendering)(struct s_app*, double, double))
{
    int start_x = tile_x;
    int start_y = tile_y;
    int end_x = tile_x + TILE_SIDE;
    int end_y = tile_y + TILE_SIDE;
    
    if (end_x > WIN_WIDTH) 
		end_x = WIN_WIDTH;
    if (end_y > WIN_HEIGHT) 
		end_y = WIN_HEIGHT;
    
    for (int y = start_y; y < end_y; y++)
    {
        for (int x = start_x; x < end_x; x++)
        {
            draw_pixel_to_img(&app->mlx.img, x, y, 
                linear_to_srgb_color(rendering(app, x, y)).value);
        }
    }
}

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
	int					x;
	int					y;
	struct s_app		*app;
	int					cores;
	t_color_linear	(*rendering)(struct s_app*, double, double);
	int				th_idx;

	app = p;
	cores = app->threads.cpu_cores;
	th_idx = get_th_idx(&app->threads);
	if (app->scene.antialiasing.enabled)
		rendering = antialiasing;
	else
		rendering = basic_render;
	y = 0;
	x = th_idx * TILE_SIDE;
	
	while (true)
	{
		render_tile(app, x, y, rendering);
		if (!next_tile(cores, &x, &y))
			break ;

		// pthread_mutex_lock(&app->threads.print_mtx);
		// mlx_put_image_to_window(app->mlx.mlx, app->mlx.win, app->mlx.img.img, x, y);
		// pthread_mutex_unlock(&app->threads.print_mtx);
	}
	return (NULL);
}
