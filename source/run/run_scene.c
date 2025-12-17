/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:27:02 by echatela          #+#    #+#             */
/*   Updated: 2025/12/17 14:48:25 by echatela         ###   ########.fr       */
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

static inline void	trace(struct s_app *app, int x, int y)
{
	t_phong		phong;

	ft_bzero(&phong, sizeof(phong));

	init_ray(app, &phong.primary_ray, x, y);
	phong.hit_info = ray_hit(&phong.primary_ray, app->scene.elems, app->scene.n_elem);
	
	if (!phong.hit_info.did_hit)
		return (draw_pixel_to_img(&app->mlx.img, x, y, BLACK));

	phong_effect(&app->scene, &phong);
	
	draw_pixel_to_img(&app->mlx.img, x, y, phong.final_color.value);
}

static int	trace(struct s_app *app, struct s_ray *ray)
{
	t_phong	phong;

	ft_bzero(&phong, sizeof(phong));
	phong.hit_info = ray_hit(&phong.primary_ray, app->scene.elems, app->scene.n_elem);
	if (!phong.hit_info.did_hit)
		return (BLACK);
	
	phong_init;


	return (phong.final_color.value);
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
			draw_pixel_to_img(&app->mlx.img, x, y, trace(app, ));
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
