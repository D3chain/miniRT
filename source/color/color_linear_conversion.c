/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_linear_conversion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 00:09:15 by fox               #+#    #+#             */
/*   Updated: 2026/01/18 22:08:46 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

__attribute__((pure))
t_real	rgb_to_linear(t_real channel)
{
	static const t_real	chan_lim = 0.04045;
	static const t_real	v12_92 = 12.92;
	static const t_real	v1_055 = 1.055;
	static const t_real	v0_055 = 0.055;
	static const t_real	v2_4 = 2.4;

	if (channel <= chan_lim)
		return (channel / v12_92);
	else
		return (pow((channel + v0_055) / v1_055, v2_4));
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
	static const t_real	chan_lim = 0.0031308;
	static const t_real	inv2_4 = FLT_1 / 2.4;
	static const t_real	v12_92 = 12.92;
	static const t_real	v1_055 = 1.055;
	static const t_real	v0_055 = 0.055;
	
	if (channel <= chan_lim)
		return (channel * v12_92);
	else
		return (v1_055 * pow(channel, inv2_4) - v0_055);
}

__attribute__((pure))
t_color	linear_to_srgb_color(t_color_linear col)
{
	return ((t_color){
		.s_rgb.r = (uint8_t)(linear_to_srgb(col.r) * FLT_255),
		.s_rgb.g = (uint8_t)(linear_to_srgb(col.g) * FLT_255),
		.s_rgb.b = (uint8_t)(linear_to_srgb(col.b) * FLT_255),
		.s_rgb.t = 255
	});
}
