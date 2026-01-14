/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:41:15 by echatela          #+#    #+#             */
/*   Updated: 2026/01/14 13:57:37 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* phony functions for compilation */



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
