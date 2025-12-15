/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:41:15 by echatela          #+#    #+#             */
/*   Updated: 2025/12/15 13:34:32 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* phony functions for compilation */

void	cleanup_app(struct s_app *app)
{
	if (app->mlx.mlx)
	{
		if (app->mlx.win)
			mlx_destroy_window(app->mlx.mlx, app->mlx.win);
		if (app->mlx.img.img)
			mlx_destroy_image(app->mlx.mlx, app->mlx.img.img);
		mlx_destroy_display(app->mlx.mlx);
		free(app->mlx.mlx);
	}
	if (app->scene.elems)
		free(app->scene.elems);
}

void	print_error(struct s_app *app)
{
	;
}

/* ************************************************************************** */

static int	quit(struct s_app *app)
{
	print_error(app);
	cleanup_app(app);
	return (app->status);
}

int	main(int argc, char *argv[])
{
	srand(time(NULL));

	struct s_app	app;

	if (init_app(&app, argc, argv))
		return (quit(&app));
	if (load_scene(&app, argv[1]))
		return (quit(&app));
	if (run_scene(&app))
		return (quit(&app));
	return (quit(&app));
}
