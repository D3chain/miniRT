/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:20:04 by echatela          #+#    #+#             */
/*   Updated: 2026/01/07 18:42:40 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


int	event_keyboard_press(int key, struct s_app *app)
{
	if (key == XK_Escape)
		mlx_loop_end(app->mlx.mlx);
	if (key == XK_a)
	{
		app->scene.antialiasing.enabled = !app->scene.antialiasing.enabled;
		printf("Antialiasing=%d\n", app->scene.antialiasing.enabled);
		if (app->scene.antialiasing.enabled)
			printf("Oversampling=%d\n", app->scene.antialiasing.oversampling);
		render(app);
	}
	if (key == XK_z)
	{
		if (app->scene.antialiasing.enabled == false)
		{
			app->scene.antialiasing.enabled = true;
			printf("Oversampling has been enabled\n");
		}
		app->scene.antialiasing.grid_size *= 2;
		app->scene.antialiasing.oversampling = pow(app->scene.antialiasing.grid_size, 2.0);
		printf("Oversampling=%d\n", app->scene.antialiasing.oversampling);
		render(app);
	}
	if (key == XK_e)
	{
		if (app->scene.antialiasing.grid_size == 2)
		{
			app->scene.antialiasing.enabled = false;
			app->scene.antialiasing.grid_size = 1;
			printf("Oversampling has been disabled.\n");
			render(app);
		}
		else if (app->scene.antialiasing.grid_size > 2)
		{
			app->scene.antialiasing.grid_size /= 2;
			app->scene.antialiasing.oversampling = pow(app->scene.antialiasing.grid_size, 2.0);
			printf("Oversampling=%d\n", app->scene.antialiasing.oversampling);
			render(app);
		}
		else
			printf("Oversampling is already disabled.\n");
		
	}
	return (0);
}
