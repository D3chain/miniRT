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

int	init_app(struct s_app *app, int argc, char *argv[])
{
	ft_bzero(app, sizeof(*app));
	if (check_arg(app, argc, argv))
		return (app->status);
	if (init_mlx(app))
		return (app->status);
	app->scene.antialiasing = (t_antialiasing){
		.enabled = true, 
		.oversampling = OVERSAMPLING, 
		.grid_size = sqrt(OVERSAMPLING)
	};
	return (ERR_NONE);
}
