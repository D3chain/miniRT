/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:27:02 by echatela          #+#    #+#             */
/*   Updated: 2026/01/07 15:45:27 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_color_linear	trace(struct s_scene *scene, const t_ray *ray);

static inline void	init_ray(struct s_app *app, struct s_ray *ray, double x, double y)
{
	const t_double3	delta = plus3(mul3(app->scene.camera.viewport_u_px, (double)x), mul3(app->scene.camera.viewport_v_px, (double)y));
	const t_double3	px_pos = plus3(app->scene.camera.pixel00_loc, delta);

	ray->dir = minus3(px_pos, app->scene.camera.focal_center);
	ray->origin = app->scene.camera.focal_center;
}

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
	t_hit_info		hit_info;

	hit_info = ray_hit(ray, scene->elems, scene->n_elem);
	if (!hit_info.did_hit)
		return (srgb_to_linear_color((t_color){.value = BLACK}));
	return (phong_effect(scene, &hit_info));
}

void render(struct s_app *app)
{
    double x, y;
    t_ray ray;
    t_color_linear final_color_linear;
    int samples = 64;
	int	grid_size = sqrt(samples);
    double offset_x, offset_y;
    
    x = -1;
    while (++x < WIN_WIDTH)
    {
        y = -1;
        while (++y < WIN_HEIGHT)
        {
            // Réinitialiser à zéro
            final_color_linear = (t_color_linear){0, 0, 0};
            
            // Grille 4x4 pour 16 samples
            for (int sx = 0; sx < grid_size; sx++)
            {
                for (int sy = 0; sy < grid_size; sy++)
                {
                    // Offsets entre 0 et 1
                    offset_x = (sx + 0.5) / grid_size;
                    offset_y = (sy + 0.5) / grid_size;

                    init_ray(app, &ray, x + offset_x, y + offset_y);
                    
                    // SIMPLEMENT additionner
                    t_color_linear sample = trace(&app->scene, &ray);
                    final_color_linear.r += sample.r;
                    final_color_linear.g += sample.g;
                    final_color_linear.b += sample.b;
                }
            }
            
            // Diviser par le nombre total de samples
            final_color_linear.r /= samples;
            final_color_linear.g /= samples;
            final_color_linear.b /= samples;
            
            draw_pixel_to_img(&app->mlx.img, x, y, 
                linear_to_srgb_color(final_color_linear).value);
        }
    }
    mlx_put_image_to_window(app->mlx.mlx, app->mlx.win, app->mlx.img.img, 0, 0);
    printf("image printed\n");
}

/* void	render(struct s_app *app)
{
	int		x;
	int		y;
	t_ray	ray;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		y = -1;
		while (++y < WIN_HEIGHT)
		{
			init_ray(app, &ray, x, y);
			draw_pixel_to_img(&app->mlx.img, x, y, linear_to_srgb_color(trace(&app->scene, &ray)).value);
		}
	}
	mlx_put_image_to_window(app->mlx.mlx, app->mlx.win, app->mlx.img.img, 0, 0);
	printf("image printed\n");
} */

int run_scene(struct s_app *app)
{
	app->mlx.win = mlx_new_window(app->mlx.mlx, app->mlx.width, app->mlx.height, "miniRT");
	render(app);
	mlx_hook(app->mlx.win, KeyPress, KeyPressMask, event_keyboard_press, app);
	mlx_loop(app->mlx.mlx);
	return (0);
}
