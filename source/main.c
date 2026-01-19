/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:41:15 by echatela          #+#    #+#             */
/*   Updated: 2026/01/19 17:52:26 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* phony functions for compilation */



void	print_error(struct s_app *app)
{
	;
}

/* ************************************************************************** */

static int	check_arg(struct s_app *app, int argc, char *argv[])
{
	if (argc != 2 || ft_strrcmp(argv[1], ".rt"))
	{
		printf("Usage: ./%s <filename.rt>\n", argv[0]);
		return (1);
	}
	app->file_name = argv[1];
	return (ERR_NONE);
}

static int	quit(struct s_app *app)
{
	print_error(app);
	cleanup_app(app);
	return (app->status);
}

int	main(int argc, char *argv[])
{
	struct s_app	app;

	ft_memset(&app, 0, sizeof(app));
	if (check_arg(&app, argc, argv))
		return (ERR_PARS);
	if (load_scene(&app))
		return (quit(&app));
	if (init_app(&app, argc, argv))
		return (quit(&app));
	if (run_scene(&app))
		return (quit(&app));
	return (quit(&app));
}
