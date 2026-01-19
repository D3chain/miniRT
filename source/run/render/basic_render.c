/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:25:26 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/19 16:25:27 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

inline t_color_linear	basic_render(struct s_app *app, t_real x, t_real y)
{
	t_ray	ray;

	init_ray(app, &ray, x, y);
	return (trace(&app->scene, &ray));
}
