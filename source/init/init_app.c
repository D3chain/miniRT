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
		ft_printf("Usage: %s <filename.rt>\n", argv[0]);
		return (1);
	}
	return (0);
}

static int	init_mlx(struct s_app *app)
{
	(void) app;
	return (0);
}

int	init_app(struct s_app *app, int argc, char *argv[])
{
	ft_bzero(app, sizeof(*app));
	if (check_arg(app, argc, argv))
		return (app->status);
	if (init_mlx(app))
		return (app->status);
	return (ERR_NONE);
}
