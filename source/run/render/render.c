/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:30:31 by fox               #+#    #+#             */
/*   Updated: 2026/01/07 17:52:09 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void render(struct s_app *app)
{
	double	x;
	double	y;
	t_color_linear	(*rendering)(struct s_app*, double, double);
	t_color_linear	final_color_linear;

	if (app->scene.antialiasing.enabled)
		rendering = antialiasing;
	else
		rendering = basic_render;

	x = 0.0;
	while (x++ < WIN_WIDTH)
	{
		y = 0.0;
		while (y++ < WIN_HEIGHT)
			draw_pixel_to_img(&app->mlx.img, x, y, 
				linear_to_srgb_color(rendering(app, x, y)).value);
	}
	mlx_put_image_to_window(app->mlx.mlx, app->mlx.win, app->mlx.img.img, 0, 0);
	printf("image printed\n");
}
