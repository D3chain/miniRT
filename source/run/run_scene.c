/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:27:02 by echatela          #+#    #+#             */
/*   Updated: 2025/11/17 19:58:14 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

__attribute__((const, hot))
double	dot(t_double3 a, t_double3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_double3	dot3(t_double3 a, t_double3 b)
{
	t_double3	res;

	res.x = a.x * b.x;
	res.y = a.y * b.y;
	res.z = a.z * b.z;
	return (res);
}

t_double3	plus3(t_double3 a, t_double3 b)
{
	t_double3	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

t_double3	minus3(t_double3 a, t_double3 b)
{
	t_double3	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

void    draw_pixel_to_img(struct s_img *img, int x, int y, int color)
{
	unsigned int	pixel;

    if (x < 0 || x > WIN_WIDTH || y < 0 || y > WIN_HEIGHT)
        return ;
    pixel = (y * img->size_line) + (x * img->bpp / 8);
    img->addr[pixel + 0] = (color) & 0xff;
    img->addr[pixel + 1] = (color >> 8) & 0xff;
    img->addr[pixel + 2] = (color >> 16) & 0xff;
    img->addr[pixel + 3] = (color >> 24) & 0xff;
}

bool	hit_sphere(struct s_ray *ray, struct s_sphere *sphere)
{
	double	a;
	double	b;
	double	c;
	double	dis;
	t_double3	off_ray_origin;

	off_ray_origin = minus3(ray->origin, sphere->coord);
	a = 1;
	b = 2 * dot(off_ray_origin, ray->dir);
	c = dot(off_ray_origin, off_ray_origin) - pow(sphere->diametre / 2, 2.0);
	dis = pow(b, 2.0) - 4 * a * c;
	;

	if (dis >= 0)
	{
		float	dst = (-b - sqrt(dis)) / (2 * a);
		if (dst >= 0)
			return (1);
	}
	return (0);
}

bool	hit(struct s_ray *ray, struct s_elem *elems, int n_elem)
{
	int	i;

	i = 0;
	while (i < n_elem)
	{
		if (elems[i].type == SPHERE && hit_sphere(ray, &elems[i].u.sphere))
			return (1);
		i++;
	}
	return (0);
}

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
	struct s_ray	ray;
	
	init_ray(&ray, x, y, app->scene.camera.coord.z);
	if (hit(&ray, app->scene.elems, app->scene.nb_elem))
		draw_pixel_to_img(&app->mlx.img, x, y, 0xFFFFFFFF);
	
}

void	render(struct s_app *app)
{
	int	x;
	int	y;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		y = -1;
		while (++y < WIN_HEIGHT) {
			trace(app, x, y);

		}
	}
	mlx_put_image_to_window(app->mlx.mlx, app->mlx.win, app->mlx.img.img, 0, 0);
}

int run_scene(struct s_app *app)
{
	app->scene.nb_elem = 1;


	
	app->mlx.win = mlx_new_window(app->mlx.mlx, app->mlx.width, app->mlx.height, "miniRT");
	render(app);
	mlx_hook(app->mlx.win, KeyPress, KeyPressMask, event_keyboard_press, app);
	mlx_loop(app->mlx.mlx);
	return (0);
}