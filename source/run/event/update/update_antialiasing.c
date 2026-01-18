/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_antialiasing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:27:45 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/18 12:07:24 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

__attribute__((always_inline))
static inline void	toggle_antialiasing(struct s_antialiasing *a)
{
	a->enabled = !a->enabled;
	printf("\nAntialiasing=%d\n", a->enabled);
	if (a->enabled)
		printf("Oversampling=%d\n\n", a->samples);
}

__attribute__((always_inline))
static inline void	increase_sample_amount(t_antialiasing *a)
{
	if (a->enabled == false)
	{
		a->enabled = true;
		printf("\nOversampling has been enabled\n");
	}
	++a->grid_size;
	a->samples = a->grid_size * a->grid_size;
	printf("Oversampling=%d\n", a->samples);
}

__attribute__((always_inline))
static inline void	decrease_sample_amount(t_antialiasing *a)
{
	if (a->grid_size == 2)
	{
		a->enabled = false;
		printf("\nOversampling has been disabled.\n");
	}
	else if (a->grid_size > 2)
	{
		--a->grid_size;
		a->samples = a->grid_size * a->grid_size;
		printf("Oversampling=%d\n", a->samples);
	}
	else
		printf("Oversampling is already disabled.\n");
}

void	update_antialiasing(int key, struct s_app *app)
{
	if (key == XK_a)	
		toggle_antialiasing(&app->render.antialiasing);
	else if (key == XK_z)
		increase_sample_amount(&app->render.antialiasing);
	else if (key == XK_e)
		decrease_sample_amount(&app->render.antialiasing);
	render(app);
}

