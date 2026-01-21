/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_linear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:21:51 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/21 12:15:14 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color_lin	add_color_linear(t_color_lin a, t_color_lin b)
{
	t_color_lin	col;

	col.r = fmin(1.0, a.r + b.r);
	col.g = fmin(1.0, a.g + b.g);
	col.b = fmin(1.0, a.b + b.b);
	return (col);
}

t_color_lin
	mul_color_linear(t_color_lin a, t_color_lin b, t_real factor)
{
	return (
		(t_color_lin){\
			a.r * b.r * factor, \
			a.g * b.g * factor, \
			a.b * b.b * factor \
		} \
	);
}

t_color_lin	scale_color_linear(t_color_lin col, t_real factor)
{
	col.r *= factor;
	col.g *= factor;
	col.b *= factor;
	return (col);
}
