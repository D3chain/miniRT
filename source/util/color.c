/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:18:39 by echatela          #+#    #+#             */
/*   Updated: 2025/12/16 17:14:50 by fox              ###   ########.fr       */
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

/****************** */

double	srgb_to_linear(double channel)
{
	if (channel <= 0.04045f)
		return (channel / 12.92f);
	else
		return (powf((channel + 0.055) / 1.055, 2.4));
}

t_color_linear	srgb_to_linear_color(t_color color)
{
	return ((t_color_linear){
		srgb_to_linear(color.s_rgb.r),
		srgb_to_linear(color.s_rgb.g),
		srgb_to_linear(color.s_rgb.b)
	});
}

/************ */

double linear_to_srgb(double channel)
{
    if (channel <= 0.0031308)
        return (channel * 12.92);
    else
        return (1.055 * powf(channel, 1.0/2.4) - 0.055);
}

// Approximation simple
t_color linear_to_srgb_approx(t_color_linear color)
{
	static const double	exp = 1.0/2.2;
	
    return ((t_color){
        powf(color.r, exp),
        powf(color.g, exp),
        powf(color.b, exp)
    });
}



/**************** */

// Addition
t_color_linear color_add_linear(t_color_linear a, t_color_linear b)
{
    return (t_color_linear){
        a.r + b.r,
        a.g + b.g,
        a.b + b.b,
        a.t + b.t
    };
}

// Multiplication composante par composante
t_color_linear color_multiply_linear(t_color_linear a, t_color_linear b)
{
    return (t_color_linear){
        a.r * b.r,
        a.g * b.g,
        a.b * b.b,
        a.t * b.t
    };
}

// Multiplication par un scalaire
t_color_linear color_scale_linear(t_color_linear c, double factor)
{
    return (t_color_linear){
        c.r * factor,
        c.g * factor,
        c.b * factor,
        c.t * factor
    };
}

// Interpolation linéaire (utile pour les dégradés)
t_color_linear color_lerp_linear(t_color_linear a, t_color_linear b, double t)
{
    return (t_color_linear){
        a.r + (b.r - a.r) * t,
        a.g + (b.g - a.g) * t,
        a.b + (b.b - a.b) * t,
        a.t + (b.t - a.t) * t
    };
}