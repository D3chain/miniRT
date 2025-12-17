/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_linear_conversion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 00:09:15 by fox               #+#    #+#             */
/*   Updated: 2025/12/17 00:23:23 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	rgb_to_linear(double channel)
{
	if (channel <= 0.04045)
		return (channel / 12.92);
	else
		return (pow((channel + 0.055) / 1.055, 2.4));
}
t_color_linear	srgb_to_linear_color(t_color color)
{
	return (t_color_linear){
		rgb_to_linear(color.s_rgb.r / 255.0),
		rgb_to_linear(color.s_rgb.g / 255.0),
		rgb_to_linear(color.s_rgb.b / 255.0),
		1.0
	};
}

double	linear_to_srgb(double channel)
{
	if (channel <= 0.0031308)
		return (channel * 12.92);
	else
		return (1.055 * pow(channel, 1.0/2.4) - 0.055);
}

t_color	linear_to_srgb_color(t_color_linear col)
{
	t_color res;
	
	col.r = fmin(fmax(col.r, 0.0), 1.0);
	col.g = fmin(fmax(col.g, 0.0), 1.0);
	col.b = fmin(fmax(col.b, 0.0), 1.0);
	res.s_rgb.r = (uint8_t)(linear_to_srgb(col.r) * 255.0);
	res.s_rgb.g = (uint8_t)(linear_to_srgb(col.g) * 255.0);
	res.s_rgb.b = (uint8_t)(linear_to_srgb(col.b) * 255.0);
	res.s_rgb.t = 255;
	return (res);
}
