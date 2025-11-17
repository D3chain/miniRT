/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:18:39 by echatela          #+#    #+#             */
/*   Updated: 2025/11/17 18:33:58 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	color_trgb(int r, int g, int b, int t)
{
	t_color	color;

	color.s_rgb.r = r;
	color.s_rgb.g = g;
	color.s_rgb.b = b;
	color.s_rgb.t = t;
	return (color);
}

t_color	color_int(int color_value)
{
	t_color	color;

	color.value = color_value;
	return (color);
}
