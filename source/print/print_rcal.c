/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rcal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:24:47 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/20 19:23:00 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_r(struct s_app *app, int fd)
{
	dprintf(fd, "R\t"INT"\t"INT"\n\n", \
		app->mlx.screen.resolution.x, \
		app->mlx.screen.resolution.y);
}

static void	print_c(struct s_app *app, int fd)
{
	dprintf(fd, "C\t"REAL3"\t"REAL3"\t"FLT_FMT"\n\n",
		app->scene.camera.focal_center.x,
		app->scene.camera.focal_center.y,
		app->scene.camera.focal_center.z,
		app->scene.camera.dir.x,
		app->scene.camera.dir.y,
		app->scene.camera.dir.z,
		app->scene.camera.fov);
}

static void	print_a(struct s_app *app, int fd)
{
	dprintf(fd, "A\t"FLT_FMT"\t"COLOR_RGB"\n\n",
		app->scene.ambient.ratio,
		app->scene.ambient.color.s_rgb.r,
		app->scene.ambient.color.s_rgb.g,
		app->scene.ambient.color.s_rgb.b \
	);
}

static void	print_l(struct s_app *app, int fd)
{
	int	i;

	i = -1;
	while (++i < app->scene.n_light)
	{
		dprintf(fd, "L\t"REAL3"\t"REAL"\t"COLOR_RGB"\n",
			app->scene.light[i].coord.x,
			app->scene.light[i].coord.y,
			app->scene.light[i].coord.z,
			app->scene.light[i].ratio,
			app->scene.light[i].color.s_rgb.r,
			app->scene.light[i].color.s_rgb.g,
			app->scene.light[i].color.s_rgb.b \
		);
	}
	dprintf(fd, "\n");
}

void	print_rcal(struct s_app *app, int fd)
{
	print_r(app, fd);
	print_c(app, fd);
	print_a(app, fd);
	print_l(app, fd);
}
