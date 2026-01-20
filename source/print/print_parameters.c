/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:24:08 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/20 19:21:12 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_render(struct s_app *app)
{
	static const char	*state[] = {"OFF", "ON"};

	printf("\n");
	printf("╔═══════════════════════════════════╗\n");
	printf("║       RENDER CONFIGURATION        ║\n");
	printf("╚═══════════════════════════════════╝");
	printf("\n  Resolution    : %-dx%d", app->mlx.screen.resolution.x, \
											app->mlx.screen.resolution.y);
	printf("\n  FOV           : %-d°", (int)app->scene.camera.fov);
	printf("\n  Render cores  : %-5d", app->threads.cpu_cores);
	printf("\n  Tiles         : %-d (%dx%d)", app->render.n_tiles, \
												app->render.tile_side, \
												app->render.tile_side);
	printf("\n  Antialiasing  : %-s", \
		state[app->render.antialiasing.enabled]);
	if (app->render.antialiasing.enabled)
		printf(" (%-dx)", app->render.antialiasing.samples);
	printf("\n  Downsampling  : %-s", \
			state[app->render.antialiasing.downsample_activation]);
	if (app->render.antialiasing.downsample_activation)
		printf(" (%-dx)", app->render.antialiasing.downsample_rate);
	printf("\n\n");
}

void	print_camera(struct s_app *app)
{
	printf("╔════════════════════════════════╗\n");
	printf("║          CAMERA SETUP          ║\n");
	printf("╚════════════════════════════════╝\n");
	print_real3(app->scene.camera.focal_center, "  Pos : ");
	print_real3(app->scene.camera.dir, "  Dir : ");
	printf("  Fov : %-d°", (int)app->scene.camera.fov);
	printf("\n\n");
}
