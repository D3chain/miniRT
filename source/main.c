/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:41:15 by echatela          #+#    #+#             */
/*   Updated: 2025/11/17 11:51:01 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* phony functions for compilation */
int process_scene(struct s_app *app)
{
	(void) app;
	return (1);
}

void	cleanup_app(struct s_app *app)
{
	(void) app;
}

void	mlx_create(void)
{
	void	*mlx = mlx_init();
	(void) mlx;
	mlx_destroy_display(mlx);
}

int		load_scene(struct s_app *app, char *arg)
{
	(void) app;
	(void) arg;
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
	struct s_app	app;

	if (init_app(&app, argc, argv))
		return (quit(&app));
	if (load_scene(&app, argv[1]))
		return (quit(&app));
	if (process_scene(&app))
		return (quit(&app));
	return (quit(&app));
}
