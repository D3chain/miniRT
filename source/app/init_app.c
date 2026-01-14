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
	mlx.width = WIN_WIDTH;
	mlx.height = WIN_HEIGHT;
	mlx.img.img = mlx_new_image(mlx.mlx, mlx.width, mlx.height);
	if (!mlx.img.img)
	{
		mlx_destroy_display(mlx.mlx);
		return (app->status = ERR_MLX);
	}
	mlx.img.addr = mlx_get_data_addr(mlx.img.img, &mlx.img.bpp, &mlx.img.size_line, &mlx.img.endian);
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
	app->scene.antialiasing.enabled = true;
	app->scene.antialiasing.oversampling = OVERSAMPLING;
	app->scene.antialiasing.grid_size = sqrt(OVERSAMPLING);
	app->render.resolution = WIN_WIDTH * WIN_HEIGHT;
	app->render.tile_side = TILE_SIDE;
	app->render.tile_area  = TILE_SIDE * TILE_SIDE;
	app->render.n_tiles = ceil((t_real) app->render.resolution / app->render.tile_area);
}

int	init_app(struct s_app *app, int argc, char *argv[])
{
	ft_memset(app, 0, sizeof(*app));
	if (check_arg(app, argc, argv))
		return (app->status);
	if (init_mlx(app))
		return (app->status);
	init_graphic_data(app);
	if (init_threads(app))
		return (app->status);
	return (ERR_NONE);
}
