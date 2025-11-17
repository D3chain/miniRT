/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:18:39 by echatela          #+#    #+#             */
/*   Updated: 2025/11/17 15:18:51 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	color_trgb(int r, int g, int b, int t)
{
	t_rgb	color;

	color.s_rgb.r = r;
	color.s_rgb.g = g;
	color.s_rgb.b = b;
	color.s_rgb.t = t;
	return (color);
}

t_rgb	color_int(int color_value)
{
	t_rgb	color;

	color.color = color_value;
	return (color);
}
