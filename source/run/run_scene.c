/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:27:02 by echatela          #+#    #+#             */
/*   Updated: 2025/11/17 16:18:15 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int run_scene(struct s_app *app)
{
	app->mlx.win = mlx_new_window(app->mlx.mlx, app->mlx.width, app->mlx.height, "miniRT");
	mlx_hook(app->mlx.win, KeyPress, KeyPressMask, event_keyboard_press, app);
	mlx_loop(app->mlx.mlx);
	return (0);
}