/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_keyboard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:20:04 by echatela          #+#    #+#             */
/*   Updated: 2026/01/16 21:59:25 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline void	print_camera(struct s_app *app)
{
	printf("CAMERA:\n");
	print_real3(app->scene.camera.focal_center, "\tposition:");
	print_real3(app->scene.camera.dir, "\tdirection:");
}

int	event_keyboard_press(int key, struct s_app *app)
{
	if (key == XK_Escape)
		mlx_loop_end(app->mlx.mlx);
	else if (key == XK_a || key == XK_z || key == XK_e)
		update_antialiasing(key, app);
	else if (key == XK_p)
		print_camera(app);
	else if (key == XK_equal || key == XK_minus || key == XK_BackSpace)
		zoom_speed(key, app);
	return (0);
}
