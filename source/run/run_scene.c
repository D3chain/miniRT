/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:27:02 by echatela          #+#    #+#             */
/*   Updated: 2025/12/08 16:47:38 by echatela         ###   ########.fr       */
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

void	init_ray(struct s_app *app, struct s_ray *ray, int x, int y)
{
	const t_double3	delta = plus3(mul3(app->scene.camera.viewport_u_px, (double)x), mul3(app->scene.camera.viewport_v_px, (double)y));
	const t_double3	px_pos = plus3(app->scene.camera.pixel00_loc, delta);

	ray->dir = minus3(px_pos, app->scene.camera.focal_center);
	ray->origin = app->scene.camera.focal_center;

}

void	trace(struct s_app *app, int x, int y)
{
	struct s_ray		ray;
	struct s_hit_info	hit_info;
	
	init_ray(app, &ray, x, y);

	hit_info = ray_hit(&ray, app->scene.elems, app->scene.n_elem);

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
