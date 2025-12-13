/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:27:02 by echatela          #+#    #+#             */
/*   Updated: 2025/12/13 17:23:08 by echatela         ###   ########.fr       */
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
	struct s_hit_info	hit_info_1;
	struct s_hit_info	hit_info_2;
	t_color				color_light;
	t_color				color_ambient;
	t_color				color;
	
	init_ray(app, &ray, x, y);

	hit_info_1 = ray_hit(&ray, app->scene.elems, app->scene.n_elem);
	ray.dir = normalize3(minus3(app->scene.light.coord, hit_info_1.hit_point));
	ray.origin = hit_info_1.hit_point;

	double	ratio = dot(hit_info_1.normal, ray.dir);;

	if (ratio < EPSILON)
		ratio = 0.0;
	else
	{
		hit_info_2 = ray_hit(&ray, app->scene.elems, app->scene.n_elem);
		if (hit_info_2.did_hit
			&& ft_dblcmp(hit_info_2.dst,
				norm3(minus3(app->scene.light.coord, ray.origin)), EPSILON) < 0.0)
			ratio = 0.0;
	}
	// ratio = fmin(1.0, ratio + app->scene.ambient.ratio);
	color_light = mul_color(hit_info_1.color_material, app->scene.light.color, ratio * app->scene.light.ratio);

	color_ambient = mul_color(hit_info_1.color_material, app->scene.ambient.color, app->scene.ambient.ratio);
	color = color_add(color_ambient, color_light);

	draw_pixel_to_img(&app->mlx.img, x, y, color.value);
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
	printf("caca\n");
}

int run_scene(struct s_app *app)
{
	app->mlx.win = mlx_new_window(app->mlx.mlx, app->mlx.width, app->mlx.height, "miniRT");
	render(app);
	mlx_hook(app->mlx.win, KeyPress, KeyPressMask, event_keyboard_press, app);
	mlx_loop(app->mlx.mlx);
	return (0);
}
