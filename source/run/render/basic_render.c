/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:25:26 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/21 12:15:14 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

inline t_color_lin	basic_render(t_app *app, t_real x, t_real y)
{
	t_ray	ray;

	init_ray(app, &ray, x, y);
	return (trace(&app->scene, &ray));
}
