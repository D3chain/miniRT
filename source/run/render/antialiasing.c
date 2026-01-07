/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:41:29 by fox               #+#    #+#             */
/*   Updated: 2026/01/07 17:53:46 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline t_color_linear	increment_linear_color(t_color_linear incremented, t_color_linear with)
{
	incremented.r += with.r;
	incremented.g += with.g;
	incremented.b += with.b;
	return (incremented);
}

static inline t_color_linear	average_linear_color(t_color_linear incremented, int samples)
{
	incremented.r /= samples;
	incremented.g /= samples;
	incremented.b /= samples;
	return (incremented);
}

t_color_linear	antialiasing(struct s_app *app, double x, double y)
{
	t_antialiasing	alias;
	t_ray			ray;
	t_color_linear	final_color_linear;

	final_color_linear = (t_color_linear){0};
	
	alias = app->scene.antialiasing;
	
	for (int sx = 0; sx < alias.grid_size; sx++)
	{
		for (int sy = 0; sy < alias.grid_size; sy++)
		{
			alias.xy_offset.x = (sx + 0.5) / alias.grid_size;
			alias.xy_offset.y = (sy + 0.5) / alias.grid_size;

			init_ray(app, &ray, x + alias.xy_offset.x, y + alias.xy_offset.y);
			
			final_color_linear = increment_linear_color(final_color_linear, trace(&app->scene, &ray));
		}
	}
	return (average_linear_color(final_color_linear, alias.oversampling));
}
