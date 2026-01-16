/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_RCAL.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:17:32 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/16 15:39:31 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	complete_R(struct s_app *app, struct s_screen *screen)
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

void	complete_C(struct s_app *app, struct s_camera *camera, bool setup_pan_speed)
{
	camera->dir = normalize3(camera->dir);
	camera->focal_length = FOCAL_LENGTH;
	camera->fov_rad = ft_toradian(camera->fov);
	camera->wp.height = 2.0 * tan(camera->fov_rad / 2.0) * camera->focal_length;
	camera->wp.width = camera->wp.height * app->mlx.screen.img_ratio;
	if (camera->dir.y > 0.99 || camera->dir.y < -0.99)
		camera->wp.u = (t_real3){1.0, 0.0, 0.0};
	else
		camera->wp.u = fmul3(normalize3(cross3(camera->dir, (t_real3){0.0, -1.0, 0.0})), camera->wp.width);
	camera->wp.u_px = fmul3(camera->wp.u, 1.0 / app->mlx.screen.resolution.x);
	camera->wp.v = fmul3(normalize3(cross3(camera->dir, camera->wp.u)), -camera->wp.height);
	camera->wp.v_px = fmul3(camera->wp.v, 1.0 / app->mlx.screen.resolution.y);
	camera->wp.upper_left = minus3(plus3(camera->focal_center, camera->dir), plus3(fmul3(camera->wp.u, 0.5), fmul3(camera->wp.v, 0.5)));
	camera->wp.pixel00_loc = plus3(plus3(camera->wp.upper_left, fmul3(camera->wp.u_px, 0.5)),
			fmul3(camera->wp.v_px, 0.5));
	if (setup_pan_speed)
	{
		app->scene.camera.mouse.zoom.base_pan_speed = ZOOM_BASE_PAN_SPEED;
		app->scene.camera.fov_reference = ZOOM_FOV_REFERENCE;
		app->scene.camera.pan_fov_ratio = app->scene.camera.fov / ZOOM_FOV_REFERENCE;
		app->scene.camera.mouse.zoom.pan_speed = ZOOM_BASE_PAN_SPEED * app->scene.camera.pan_fov_ratio;
	}
}

void	complete_A(struct s_app *app, struct s_ambient *ambient)
{
	if (ambient->ratio > 1.0)
		ambient->ratio = 1.0;
	if (ambient->ratio < 0.0)
		ambient->ratio = 0.0;
	ambient->color_linear = srgb_to_linear_color(ambient->color);
}

void	complete_L(struct s_app *app, struct s_light *light)
{
	if (light->ratio > 1.0)
		light->ratio = 1.0;
	if (light->ratio < 0.0)
		light->ratio = 0.0;
	light->color_linear = srgb_to_linear_color(light->color);
}

void	complete_RCAL(struct s_app *app)
{
	int	i;

	complete_R(app, &app->mlx.screen);
	complete_C(app, &app->scene.camera, true);
	complete_A(app, &app->scene.ambient);
	i = -1;
	while (++i < app->scene.n_light)
		complete_L(app, &app->scene.light[i]);	
}
