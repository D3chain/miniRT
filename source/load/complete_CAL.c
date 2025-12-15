/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:17:32 by cgajean           #+#    #+#             */
/*   Updated: 2025/12/15 15:19:33 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	complete_A(struct s_app *app, struct s_ambient *ambient)
{
	if (ambient->ratio > 1.0)
		ambient->ratio = 1.0;
	if (ambient->ratio < 0.0)
		ambient->ratio = 0.0;
}

void	complete_C(struct s_app *app, struct s_camera *camera)
{
	camera->focal_length = FOCAL_LENGTH;
	camera->fov_rad = ft_toradian(camera->fov);
	camera->viewport_height = 2.0 * tan(camera->fov_rad / 2.0) * camera->focal_length;
	camera->viewport_width = camera->viewport_height * IMG_RATIO;
	if (camera->dir.y > 0.99 || camera->dir.y < -0.99)
		camera->viewport_u = (t_double3){1.0, 0.0, 0.0};
	else
		camera->viewport_u = mul3(normalize3(cross3(camera->dir, (t_double3){0.0, -1.0, 0.0})), camera->viewport_width);
	camera->viewport_u_px = mul3(camera->viewport_u, 1.0 / WIN_WIDTH);
	camera->viewport_v = mul3(normalize3(cross3(camera->dir, camera->viewport_u)), -camera->viewport_height);
	camera->viewport_v_px = mul3(camera->viewport_v, 1.0 / WIN_HEIGHT);
	camera->viewport_upper_left = minus3(plus3(camera->focal_center, camera->dir), plus3(mul3(camera->viewport_u, 0.5), mul3(camera->viewport_v, 0.5)));
	camera->pixel00_loc = plus3(plus3(camera->viewport_upper_left, mul3(camera->viewport_u_px, 0.5)),
			mul3(camera->viewport_v_px, 0.5));
}

void	complete_L(struct s_app *app, struct s_light *light)
{
	if (light->ratio > 1.0)
		light->ratio = 1.0;
	if (light->ratio < 0.0)
		light->ratio = 0.0;
}
