/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:41:15 by echatela          #+#    #+#             */
/*   Updated: 2026/01/23 13:18:00 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#ifdef LOAD_PRO

static void	print_error(t_app *app)
{
	if (app->status == ERR_SYS)
		dprintf(STDERR_FILENO, \
			"Fatal system error, restart MiniRT.\n");
	else if (app->status == ERR_MLX)
		dprintf(STDERR_FILENO, \
			"Fatal MLX error, restart MiniRT.\n");
	else if (app->status == ERR_PARS)
		dprintf(STDERR_FILENO, \
			"Parsing error, restart MiniRT with a valid [filename.rt] file.\n");
}

#else

static void	print_error(t_app *app)
{
	char	*err_msg;

	if (app->status == ERR_SYS)
		err_msg = "Fatal system error, restart MiniRT.\n";
	else if (app->status == ERR_MLX)
		err_msg = "Fatal MLX error, restart MiniRT.\n";
	else if (app->status == ERR_PARS)
		err_msg = \
			"Parsing error, restart MiniRT with a valid [filename.rt] file.\n";
	else
		err_msg = "";
	if (*err_msg)
		write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
}
#endif

static int	check_arg(t_app *app, int argc, char *argv[])
{
	if (argc != 2 || ft_strrcmp(argv[1], ".rt"))
	{
		printf("Usage: %s <filename.rt>\n", argv[0]);
		return (app->status = ERR_PARS);
	}
	app->file_name = argv[1];
	return (ERR_NONE);
}

static int	quit(t_app *app)
{
	print_error(app);
	cleanup_app(app);
	return (app->status);
}

int	main(int argc, char *argv[])
{
	t_app	app;

	ft_memset(&app, 0, sizeof(app));
	if (check_arg(&app, argc, argv))
		return (ERR_PARS);
	if (load_scene(&app))
		return (quit(&app));
	if (init_app(&app))
		return (quit(&app));
	if (run_scene(&app))
		return (quit(&app));
	return (quit(&app));
}
