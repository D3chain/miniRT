/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:27:02 by echatela          #+#    #+#             */
/*   Updated: 2025/12/17 18:14:58 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define LINEAR_FACTO

static inline void	init_ray(struct s_app *app, struct s_ray *ray, int x, int y)
{
	const t_double3	delta = plus3(mul3(app->scene.camera.viewport_u_px, (double)x), mul3(app->scene.camera.viewport_v_px, (double)y));
	const t_double3	px_pos = plus3(app->scene.camera.pixel00_loc, delta);

	ray->dir = minus3(px_pos, app->scene.camera.focal_center);
	ray->origin = app->scene.camera.focal_center;

}

// static inline void	trace(struct s_app *app, int x, int y)
// {
// 	t_phong	phong;

// 	ft_bzero(&phong, sizeof(phong));

// 	init_ray(app, &phong.primary_ray, x, y);
// 	phong.hit_info = ray_hit(&phong.primary_ray, app->scene.elems, app->scene.n_elem);
	
// 	if (!phong.hit_info.did_hit)
// 		return (draw_pixel_to_img(&app->mlx.img, x, y, BLACK));

// 	phong_effect(&app->scene, &phong);
	
// 	draw_pixel_to_img(&app->mlx.img, x, linear_to_srgb_color(phong.final_color_linear).value);
// }

// static t_color_linear	transmission_effect(struct s_scene *scene, t_ray *ray, t_hit_info *hit_info)
// {

// }
static t_color_linear	trace(struct s_scene *scene, const t_ray *ray);

static t_color_linear	reflection_effect(struct s_scene *scene, const t_ray *ray, t_hit_info *hit_info)
{
	const t_ray	reflected_ray = {
		hit_info->hit_point,
		reflect(ray->dir, hit_info->normal),
	};

	return (trace(scene, &reflected_ray));
}

static t_color_linear	trace(struct s_scene *scene, const t_ray *ray)
{
	t_color_linear	phong;
	t_color_linear	reflection;
	t_color_linear	transmission;
	t_hit_info		hit_info;
	double			fresnel;

	hit_info = ray_hit(ray, scene->elems, scene->n_elem);
	if (!hit_info.did_hit)
		return (srgb_to_linear_color((t_color){.value = BLACK}));
	phong = phong_effect(scene, &hit_info);
	if (hit_info.material.kr >= EPSILON)
		reflection = reflection_effect(scene, ray, &hit_info);
	// if (hit_info.material.kt >= EPSILON)
		// transmission = transmission_effect(scene, ray, &hit_info);
	
	// fresnel poids de T et de R
	print_color_linear(reflection, "caca ");
	return (color_add_linear(scale_color_linear(phong, 1.0), scale_color_linear(reflection, 1.0)));
	// return (phong);

}

void	render(struct s_app *app)
{
	int	x;
	int	y;
	t_ray	ray;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		y = -1;
		while (++y < WIN_HEIGHT)
		{
			// trace(app, x, y);
			init_ray(app, &ray, x, y);
			draw_pixel_to_img(&app->mlx.img, x, y, linear_to_srgb_color(trace(&app->scene, &ray)).value);
		}
	}
	mlx_put_image_to_window(app->mlx.mlx, app->mlx.win, app->mlx.img.img, 0, 0);
	printf("image printed\n");
}

int run_scene(struct s_app *app)
{
	app->mlx.win = mlx_new_window(app->mlx.mlx, app->mlx.width, app->mlx.height, "miniRT");
	render(app);
	mlx_hook(app->mlx.win, KeyPress, KeyPressMask, event_keyboard_press, app);
	mlx_loop(app->mlx.mlx);
	return (0);
}
