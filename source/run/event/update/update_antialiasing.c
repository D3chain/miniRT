/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_antialiasing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:27:45 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/21 11:45:24 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

__attribute__((always_inline))
inline void	toggle_antialiasing(struct s_antialiasing *a)
{
	a->enabled = !a->enabled;
	if (a->enabled)
		a->rfn = antialiasing;
	else
		a->rfn = basic_render;
}

__attribute__((always_inline))
static inline void	increase_sample_amount(t_antialiasing *a)
{
	if (a->enabled == false)
	{
		a->enabled = true;
		a->rfn = antialiasing;
		printf("\nUpsampling is enabled\n");
	}
	++a->grid_size;
	a->inv_grid_size = FLT_1 / a->grid_size;
	a->samples = a->grid_size * a->grid_size;
	a->inv_samples = FLT_1 / (t_real)a->samples;
	a->inv_grid_size = FLT_1 / (t_real)a->grid_size;
	a->offset_factor = FLT_0_5 - a->grid_size / FLT_2;
	printf("Upsampling=%d\n", a->samples);
}

__attribute__((always_inline))
static inline void	decrease_sample_amount(t_antialiasing *a)
{
	if (a->grid_size <= 2)
	{
		a->enabled = false;
		a->rfn = basic_render;
		printf("\nUpsampling is disabled.\n");
	}
	else
	{
		--a->grid_size;
		a->inv_grid_size = FLT_1 / a->grid_size;
		a->samples = a->grid_size * a->grid_size;
		a->inv_samples = FLT_1 / (t_real)a->samples;
		a->inv_grid_size = FLT_1 / (t_real)a->grid_size;
		a->offset_factor = FLT_0_5 - a->grid_size / FLT_2;
		printf("Upsampling=%d\n", a->samples);
	}
}

void	update_antialiasing(int key, t_app *app)
{
	if (key == XK_a)
	{
		toggle_antialiasing(&app->render.antialiasing);
		printf("\nAntialiasing=%d\n", app->render.antialiasing.enabled);
		if (app->render.antialiasing.enabled)
			printf("Upsampling=%d\n\n", app->render.antialiasing.samples);
	}
	else if (key == XK_z)
		increase_sample_amount(&app->render.antialiasing);
	else if (key == XK_e)
		decrease_sample_amount(&app->render.antialiasing);
	render(app);
}
