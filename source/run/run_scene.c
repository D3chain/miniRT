/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:27:02 by echatela          #+#    #+#             */
/*   Updated: 2025/12/02 18:13:00 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void	init_ray(struct s_ray *ray, struct s_camera *camera, int x, int y)
// {
// 	const t_double3	pixel_center = plus3()
// 	ray->origin = camera->coord;
// 	ray->dir = 
// }

// void	trace(struct s_app *app, int x, int y)
// {
// 	struct s_ray	ray;
// 	int				pixel_color;
	
// 	init_ray(&ray, x, y, &app->scene.camera);
// 	ray.dir = app->scene.camera.dir;
// 	ray.origin = 
// 	pixel_color = ray_color(&ray, app->scene.elems, app->scene.n_elem);
// 	draw_pixel_to_img(&app->mlx.img, x, y, pixel_color);
// }

void	init_ray(struct s_ray *ray, int x, int y, int cam_z)
{
	ray->dir.x = 0;
	ray->dir.y = 0;
	ray->dir.z = 1;
	ray->origin.x = x - WIN_WIDTH / 2;
	ray->origin.y = -(y - WIN_HEIGHT / 2);
	ray->origin.z = cam_z;
}

void	trace(struct s_app *app, int x, int y)
{
	struct s_ray		ray;
	struct s_hit_info	hit_info;
	
	init_ray(&ray, x, y, app->scene.camera.viewport_center.z);
	hit_info = compute_ray_collision(&ray, app->scene.elems, app->scene.n_elem);

	if (hit_info.did_hit)
		draw_pixel_to_img(&app->mlx.img, x, y, hit_info.color_material.value);
	
}

void	render(struct s_app *app)
{
	int	x;
	int	y;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		y = -1;
		while (++y < WIN_HEIGHT)
			trace(app, x, y);
	}
	mlx_put_image_to_window(app->mlx.mlx, app->mlx.win, app->mlx.img.img, 0, 0);
}

int run_scene(struct s_app *app)
{
	app->mlx.win = mlx_new_window(app->mlx.mlx, app->mlx.width, app->mlx.height, "miniRT");
	render(app);
	mlx_hook(app->mlx.win, KeyPress, KeyPressMask, event_keyboard_press, app);
	mlx_loop(app->mlx.mlx);
	return (0);
}
