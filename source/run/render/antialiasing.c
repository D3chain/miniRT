/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:20:22 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/20 19:50:52 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

__attribute__((always_inline))
static inline t_color_linear
	increment_color_linear(t_color_linear incremented, t_color_linear with)
{
	incremented.r += with.r;
	incremented.g += with.g;
	incremented.b += with.b;
	return (incremented);
}

__attribute__((always_inline))
static inline t_color_linear
	average_color_linear(t_color_linear color, t_real inv_samples)
{
	return (scale_color_linear(color, inv_samples));
}

t_color_linear	antialiasing(struct s_app *app, t_real x, t_real y)
{
	const struct s_antialiasing	*aa;
	t_color_linear				color;
	t_ray						ray;
	t_real2						offset;
	t_int2						grid;

	aa = &app->render.antialiasing;
	color = (t_color_linear){0};
	grid.x = 0;
	while (grid.x < aa->grid_size)
	{
		grid.y = 0;
		while (grid.y < aa->grid_size)
		{
			offset.x = (grid.x + aa->offset_factor) * aa->inv_grid_size;
			offset.y = (grid.y + aa->offset_factor) * aa->inv_grid_size;
			init_ray(app, &ray, x + offset.x, y + offset.y);
			color = increment_color_linear(color, trace(&app->scene, &ray));
			grid.y++;
		}
		grid.x++;
	}
	return (average_color_linear(color, aa->inv_samples));
}
