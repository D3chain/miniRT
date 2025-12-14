/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:18:39 by echatela          #+#    #+#             */
/*   Updated: 2025/12/14 16:43:50 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	color_add(t_color color1, t_color color2)
{
	t_color	res;

	res.s_rgb.r = fmin(255.0, color1.s_rgb.r + color2.s_rgb.r);
	res.s_rgb.g = fmin(255.0, color1.s_rgb.g + color2.s_rgb.g);
	res.s_rgb.b = fmin(255.0, color1.s_rgb.b + color2.s_rgb.b);
	res.s_rgb.t = 255.0;
	return (res);
}

t_color	mul_color(t_color object, t_color light, double factor)
{
	t_color	res;

	res.s_rgb.b = fmin(255.0, object.s_rgb.b * (light.s_rgb.b * factor / 255.0)); 
	res.s_rgb.g = fmin(255.0, object.s_rgb.g * (light.s_rgb.g * factor / 255.0));
	res.s_rgb.r = fmin(255.0, object.s_rgb.r * (light.s_rgb.r * factor / 255.0));
	res.s_rgb.t = object.s_rgb.t;
	return (res);
}

t_color scale_color(t_color color, double factor)
{
	t_color res;
	
	res.s_rgb.r = fmin(255.0, color.s_rgb.r * factor);
	res.s_rgb.g = fmin(255.0, color.s_rgb.g * factor);
	res.s_rgb.b = fmin(255.0, color.s_rgb.b * factor);
	res.s_rgb.t = color.s_rgb.t;
	return (res);
}
