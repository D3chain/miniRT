/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:19:03 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/21 17:02:58 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# include <stdint.h>
# include "minirt_typedef.h"

union u_color
{
	uint32_t	value;
	struct {
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
		uint8_t	t;
	} s_rgb;
};

struct s_color_linear {
	t_real	b;
	t_real	g;
	t_real	r;
};

struct s_material
{
	t_color		color;
	t_color_lin	color_linear;

	t_real		ka;
	t_real		kd;
	t_real		ks;

	t_real		shininess;
	t_real		ior;
};

t_real		rgb_to_linear(t_real channel);
t_color_lin	srgb_to_linear_color(t_color color);
t_color		linear_to_srgb_color(t_color_lin linear);
t_color_lin	add_color_linear(t_color_lin a, t_color_lin b);
t_color_lin	scale_color_linear(t_color_lin c, t_real factor);
t_color_lin	mul_color_linear(t_color_lin a, t_color_lin b, t_real factor);

#endif
