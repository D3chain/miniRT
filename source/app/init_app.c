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

static int	check_arg(struct s_app *app, int argc, char *argv[])
{
	if (argc != 2 || ft_strrcmp(argv[1], ".rt"))
	{
		app->status = ERR_PARS;
		printf("Usage: ./%s <filename.rt>\n", argv[0]);
		return (1);
	}
	return (0);
}

static int	init_mlx(struct s_app *app)
{
	struct s_mlx	mlx;

	mlx = app->mlx;
	mlx.mlx = mlx_init();
	if (!mlx.mlx)
		return (app->status = ERR_MLX);
	mlx.img.img = mlx_new_image(mlx.mlx, mlx.screen.resolution.x, mlx.screen.resolution.y);
	if (!mlx.img.img)
	{
		mlx_destroy_display(mlx.mlx);
		return (app->status = ERR_MLX);
	}
	mlx.img.addr = mlx_get_data_addr(mlx.img.img, &mlx.img.bpp, &mlx.img.size_line, &mlx.img.endian);
	init_draw_function(&mlx.img);
	if (!mlx.img.addr)
	{
		mlx_destroy_image(mlx.mlx, mlx.img.img);
		mlx_destroy_display(mlx.mlx);
		return (app->status = ERR_MLX);
	}
	app->mlx = mlx;
	return (0);
}

int	init_threads(struct s_app *app)
{
	app->threads.cpu_cores = sysconf(_SC_NPROCESSORS_ONLN) - 1;
	app->threads.th_tab = xcalloc(app, app->threads.cpu_cores * sizeof(struct s_thread));
	return (app->status);
}

void	init_graphic_data(struct s_app *app)
{
	app->render.antialiasing.enabled = true;
	app->render.antialiasing.samples = OVERSAMPLING;
	app->render.antialiasing.inv_samples = FLT_1 / OVERSAMPLING;
	app->render.antialiasing.grid_size = sqrt(OVERSAMPLING);
	app->render.antialiasing.inv_grid_size = FLT_1 / app->render.antialiasing.grid_size;
	app->render.resolution = app->mlx.screen.resolution.x * app->mlx.screen.resolution.y;
	app->render.antialiasing.offset_factor = FLT_0_5 - app->render.antialiasing.grid_size / FLT_2;
	app->render.tile_side = TILE_SIDE;
	app->render.tile_area  = TILE_SIDE * TILE_SIDE;
	app->render.n_tiles = ceil((t_real) app->render.resolution / app->render.tile_area);
	while (app->render.n_tiles < app->threads.cpu_cores && app->render.tile_side > 1)
	{
		app->render.tile_side /= 2;
		app->render.tile_area = app->render.tile_side * app->render.tile_side;
		app->render.n_tiles = (app->render.resolution + app->render.tile_area - 1) / app->render.tile_area;
	}
	print_render(app);
}

int	init_app(struct s_app *app, int argc, char *argv[])
{
	if (check_arg(app, argc, argv))
		return (app->status);
	if (init_mlx(app))
		return (app->status);
		if (init_threads(app))
			return (app->status);
	init_graphic_data(app);
	return (ERR_NONE);
}
