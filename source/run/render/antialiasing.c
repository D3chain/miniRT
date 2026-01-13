/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:41:29 by fox               #+#    #+#             */
/*   Updated: 2026/01/13 16:48:26 by cgajean          ###   ########.fr       */
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

t_color_linear	antialiasing(struct s_app *app, t_real x, t_real y)
{
	t_antialiasing	alias;
	t_ray			ray;
	t_color_linear	final_color_linear;
	t_real			offset;

	final_color_linear = (t_color_linear){0};
	
	alias = app->scene.antialiasing;
	
	for (int sx = 0; sx < alias.grid_size; sx++)
	{
		for (int sy = 0; sy < alias.grid_size; sy++)
		{
			offset = 0.0;
			if (alias.grid_size % 2)
				offset = 1.0 / alias.grid_size;		
			alias.xy_offset.x = (sx + offset - alias.grid_size / 2) / alias.grid_size;
			alias.xy_offset.y = (sy + offset - alias.grid_size / 2) / alias.grid_size;


			init_ray(app, &ray, x + alias.xy_offset.x, y + alias.xy_offset.y);
			
			final_color_linear = increment_linear_color(final_color_linear, trace(&app->scene, &ray));
		}
	}
	return (average_linear_color(final_color_linear, alias.oversampling));
}
