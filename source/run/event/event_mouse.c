/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:03:24 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/14 17:45:59 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	event_mouse_close(struct s_app *app)
{
	mlx_loop_end(app->mlx.mlx);
	return (0);
}

int	event_mouse_click(int button, int x, int y, struct s_app *app)
{
	struct s_mouse	m;
	
	update_mouse(&app->render.mouse, button, x, y);

	if(button == Button4)
	{
		update_camera(&app->scene.camera, 1);
		complete_scene(app, &app->scene);
		render(app);
	}
	else if(button == Button5)
	{
		update_camera(&app->scene.camera, -1);
		complete_scene(app, &app->scene);
		render(app);
	}
	return (0);
}

int	event_mouse_release(int button, int x, int y, struct s_app *app)
{
	update_mouse(&app->render.mouse, button, x, y);

	if (button == Button1)
	{
		bvh_update_coord(app->scene.bvh_root, app->render.mouse.dir);
		complete_scene(app, &app->scene);
		bound_boxes(app->scene.bvh_root);
		render(app);
	}

	return (0);
}
