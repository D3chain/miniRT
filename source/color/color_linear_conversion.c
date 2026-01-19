/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_linear_conversion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:23:59 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/19 16:24:01 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#ifdef USE_DBL_NUMBER

# define CHAN_LIM	0.0031308
# define V2_4		2.4
# define INV_2_4	0.416666667
# define V_12_92	12.92
# define V_1_055	1.055
# define V_0_055	0.055

# else

# define CHAN_LIM	0.0031308f
# define V_2_4		2.4f
# define INV_2_4	0.416666667f
# define V_12_92	12.92f
# define V_1_055	1.055f
# define V_0_055	0.055f

#endif

__attribute__((pure))
t_real	rgb_to_linear(t_real channel)
{
	if (channel <= CHAN_LIM)
		return (channel / V_12_92);
	else
		return (pow((channel + V_0_055) / V_1_055, V_2_4));
}

__attribute__((pure))
t_color_linear	srgb_to_linear_color(t_color color)
{
	return (t_color_linear){
		rgb_to_linear(color.s_rgb.r / FLT_255),
		rgb_to_linear(color.s_rgb.g / FLT_255),
		rgb_to_linear(color.s_rgb.b / FLT_255),
	};
}

__attribute__((always_inline, pure))
static inline t_real	linear_to_srgb(t_real channel)
{
	if (channel <= CHAN_LIM)
		return (channel * V_12_92);
	else
		return (V_1_055 * pow(channel, INV_2_4) - V_0_055);
}

__attribute__((pure))
t_color	linear_to_srgb_color(t_color_linear col)
{
	return ((t_color){
		.s_rgb.r = (uint8_t)(linear_to_srgb(col.r) * FLT_255),
		.s_rgb.g = (uint8_t)(linear_to_srgb(col.g) * FLT_255),
		.s_rgb.b = (uint8_t)(linear_to_srgb(col.b) * FLT_255),
		.s_rgb.t = FLT_255
	});
}
