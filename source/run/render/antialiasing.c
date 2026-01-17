/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:41:29 by fox               #+#    #+#             */
/*   Updated: 2026/01/17 12:44:16 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

__attribute__((always_inline))
static inline t_color_linear	increment_linear_color(t_color_linear incremented, t_color_linear with)
{
	incremented.r += with.r;
	incremented.g += with.g;
	incremented.b += with.b;
	return (incremented);
}

__attribute__((always_inline))
static inline t_color_linear	average_linear_color(t_color_linear incremented, int samples)
{
	incremented.r /= samples;
	incremented.g /= samples;
	incremented.b /= samples;
	return (incremented);
}

__attribute__((always_inline))
static inline t_real	offset(struct s_app *app, t_real x, t_real y)
{
	
}

t_color_linear	antialiasing(struct s_app *app, t_real x, t_real y)
{
	t_real			offset_factor;
	t_antialiasing	alias;
	t_ray			ray;
	t_color_linear	final_color_linear;
	t_int2			grid;

	offset_factor = FLT_0_5 - alias.grid_size / FLT_2;
	alias = app->render.antialiasing;
	final_color_linear = (t_color_linear){0};
	grid.x = 0;
	while (grid.x < alias.grid_size)
	{
		grid.y = 0;
		while (grid.y < alias.grid_size)
		{
			alias.xy_offset.x = (grid.x + offset_factor) / alias.grid_size;
			alias.xy_offset.y = (grid.y + offset_factor) / alias.grid_size;

			init_ray(app, &ray, x + alias.xy_offset.x, y + alias.xy_offset.y);
			
			final_color_linear = increment_linear_color(final_color_linear, trace(&app->scene, &ray));
			++grid.y;	
		}
		++grid.x;
	}
	return (average_linear_color(final_color_linear, alias.oversampling));
}
