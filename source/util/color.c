/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:18:39 by echatela          #+#    #+#             */
/*   Updated: 2025/12/03 11:52:45 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	color_blend(t_color object, t_color light)
{
	t_color	col;

	col.s_rgb.r = fmin(255.0, (object.s_rgb.r / 255.0) * light.s_rgb.r);
	col.s_rgb.g = fmin(255.0, (object.s_rgb.g / 255.0) * light.s_rgb.g);
	col.s_rgb.b = fmin(255.0, (object.s_rgb.b / 255.0) * light.s_rgb.b);
	col.s_rgb.t = 255.0;
	return (col);
}
