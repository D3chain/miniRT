/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_RCAL.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:24:55 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/19 16:24:57 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	setup_R(struct s_app *app, struct s_screen *screen)
{
	if (screen->resolution.x < 1 || screen->resolution.y < 1)
	{
		screen->resolution.x = WIN_WIDTH;
		screen->resolution.y = WIN_HEIGHT;
		screen->img_ratio = IMG_RATIO;
	}
	else
		screen->img_ratio = (t_real) screen->resolution.x / screen->resolution.y;
}

void	setup_C(struct s_app *app, struct s_camera *camera, bool setup_pan_speed)
{
	camera->dir = normalize3(camera->dir);
	camera->focal_length = FOCAL_LENGTH;
	camera->fov_rad = ft_toradian(camera->fov);
	setup_viewport(app, &app->scene.camera);
	if (setup_pan_speed)
	{
		app->scene.camera.mouse.base_pan_speed = ZOOM_BASE_PAN_SPEED;
		app->scene.camera.fov_reference = FOV_REFERENCE;
		app->scene.camera.pan_fov_ratio = app->scene.camera.fov / FOV_REFERENCE;
		app->scene.camera.mouse.pan_speed = ZOOM_BASE_PAN_SPEED * app->scene.camera.pan_fov_ratio;
	}
}

void	setup_A(struct s_app *app, struct s_ambient *ambient)
{
	if (ambient->ratio > FLT_1)
		ambient->ratio = FLT_1;
	if (ambient->ratio < FLT_0)
		ambient->ratio = FLT_0;
	ambient->color_linear = srgb_to_linear_color(ambient->color);
}

void	setup_L(struct s_app *app, struct s_light *light)
{
	if (light->ratio > FLT_1)
		light->ratio = FLT_1;
	if (light->ratio < FLT_0)
		light->ratio = FLT_0;
	light->color_linear = srgb_to_linear_color(light->color);
}

void	setup_RCAL(struct s_app *app)
{
	int	i;

	setup_R(app, &app->mlx.screen);
	setup_C(app, &app->scene.camera, true);
	setup_A(app, &app->scene.ambient);
	i = -1;
	while (++i < app->scene.n_light)
		setup_L(app, &app->scene.light[i]);	
}
