/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_app.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:05:05 by echatela          #+#    #+#             */
/*   Updated: 2025/11/17 11:41:34 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_antialiasing(t_app *app)
{
	app->render.antialiasing.enabled = UPSAMPLING_INIT_ACTIV;
	app->render.antialiasing.rfn = antialiasing;
	app->render.antialiasing.tfn = render_tile;
	app->render.antialiasing.samples = UPSAMPLING;
	app->render.antialiasing.inv_samples = FLT_1 / UPSAMPLING;
	app->render.antialiasing.grid_size = sqrt(UPSAMPLING);
	app->render.antialiasing.inv_grid_size = \
		FLT_1 / app->render.antialiasing.grid_size;
	app->render.antialiasing.offset_factor = \
		FLT_0_5 - app->render.antialiasing.grid_size / FLT_2;
	app->render.antialiasing.downsample_activation = \
		DOWNSAMPLING_INIT_ACTIV;
	app->render.antialiasing.downsample_state = false;
	app->render.antialiasing.downsample_rate = DOWNSAMPLING;
}

static void	init_render(t_app *app)
{
	app->render.tile_side = TILE_SIDE;
	app->render.tile_area = TILE_SIDE * TILE_SIDE;
	app->render.resolution = \
		app->mlx.screen.resolution.x * app->mlx.screen.resolution.y;
	app->render.n_tiles = \
		ceil((t_real) app->render.resolution / app->render.tile_area);
	while (app->render.n_tiles < app->threads.cpu_cores \
			&& app->render.tile_side > 1)
	{
		app->render.tile_side /= 2;
		app->render.tile_area = app->render.tile_side * app->render.tile_side;
		app->render.n_tiles = \
			(app->render.resolution + app->render.tile_area - 1) \
			/ app->render.tile_area;
	}
	app->render.inv_tile_side = FLT_1 / app->render.tile_side;
}

static int	init_threads(t_app *app)
{
	app->threads.cpu_cores = sysconf(_SC_NPROCESSORS_ONLN) - 1;
	app->threads.th_tab = \
		xcalloc(app, app->threads.cpu_cores * sizeof(t_thread));
	return (app->status);
}

static int	init_mlx(t_app *app)
{
	t_mlx	mlx;

	mlx = app->mlx;
	mlx.mlx = mlx_init();
	if (!mlx.mlx)
		return (app->status = ERR_MLX);
	mlx.img.img = mlx_new_image(\
		mlx.mlx, mlx.screen.resolution.x, mlx.screen.resolution.y);
	if (!mlx.img.img)
	{
		mlx_destroy_display(mlx.mlx);
		return (app->status = ERR_MLX);
	}
	mlx.img.addr = mlx_get_data_addr(\
		mlx.img.img, &mlx.img.bpp, &mlx.img.size_line, &mlx.img.endian);
	if (!mlx.img.addr)
	{
		mlx_destroy_image(mlx.mlx, mlx.img.img);
		mlx_destroy_display(mlx.mlx);
		return (app->status = ERR_MLX);
	}
	app->mlx = mlx;
	return (0);
}

int	init_app(t_app *app)
{
	if (init_mlx(app))
		return (app->status);
	if (init_threads(app))
		return (app->status);
	init_render(app);
	init_antialiasing(app);
	update_camera(app, &app->scene.camera);
	print_render(app);
	return (ERR_NONE);
}
