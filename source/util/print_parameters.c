/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 12:51:08 by fox               #+#    #+#             */
/*   Updated: 2026/01/18 15:07:47 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_render(struct s_app *app)
{
	printf("\n");
	printf("╔═══════════════════════════════════╗\n");
	printf("║       RENDER CONFIGURATION        ║\n");
	printf("╚═══════════════════════════════════╝\n");
	printf("  Resolution : %-dx%d\n", app->mlx.screen.resolution.x, 
											app->mlx.screen.resolution.y);
	printf("  CPU Cores  : %-5d\n", app->threads.cpu_cores);
	printf("  Tiles      : %-d (%dx%d)\n", app->render.n_tiles, 
												app->render.tile_side,
												app->render.tile_side);
	printf("\n\n");
}


void	print_camera(struct s_app *app)
{
	printf("╔═══════════════════════════╗\n");
	printf("║        CAMERA SETUP       ║\n");
	printf("╚═══════════════════════════╝\n");
	print_real3(app->scene.camera.focal_center, "  Pos : ");
	print_real3(app->scene.camera.dir, "  Dir : ");
	printf("\n\n");
}