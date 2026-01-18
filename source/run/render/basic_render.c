/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:08:25 by fox               #+#    #+#             */
/*   Updated: 2026/01/18 18:42:43 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

inline t_color_linear	basic_render(struct s_app *app, t_real x, t_real y)
{
	t_ray	ray;

	init_ray(app, &ray, x, y);
	return (trace(&app->scene, &ray));
}
