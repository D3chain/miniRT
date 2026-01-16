/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_antialiasing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 20:27:45 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/16 22:27:54 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

__attribute__((always_inline))
static inline void	toggle_antialiasing(struct s_antialiasing *a)
{
	a->enabled = !a->enabled;
	printf("\nAntialiasing=%d\n", a->enabled);
	if (a->enabled)
		printf("Oversampling=%d\n\n", a->oversampling);
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
	a->oversampling = a->grid_size * a->grid_size;
	printf("Oversampling=%d\n", a->oversampling);
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
		a->oversampling = a->grid_size * a->grid_size;
		printf("Oversampling=%d\n", a->oversampling);
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

