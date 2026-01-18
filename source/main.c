/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:41:15 by echatela          #+#    #+#             */
/*   Updated: 2026/01/18 21:09:33 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* phony functions for compilation */



void	print_error(struct s_app *app)
{
	;
}

/* ************************************************************************** */

static int	check_arg(int argc, char *argv[])
{
	if (argc != 2 || ft_strrcmp(argv[1], ".rt"))
	{
		printf("Usage: ./%s <filename.rt>\n", argv[0]);
		return (1);
	}
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

	if (check_arg(argc, argv))
		return (ERR_PARS);
	ft_memset(&app, 0, sizeof(app));
	if (load_scene(&app, argv[1]))
		return (quit(&app));
	if (init_app(&app, argc, argv))
		return (quit(&app));
	if (run_scene(&app))
		return (quit(&app));
	return (quit(&app));
}
