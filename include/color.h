/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 16:38:48 by cgajean           #+#    #+#             */
/*   Updated: 2025/12/16 17:13:21 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <minirt.h>

# define WHITE	0xFFFFFF
# define BLACK	0x0
# define RED	0xFF0000
# define GREEN	0xFF00
# define BLUE 	0xFF

typedef union u_color			t_color;
typedef struct s_color_linear	t_color_linear;

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
	double	b;
	double	g;
	double	r;
	double	t;
};



t_color			color_add(t_color color1, t_color color2);
t_color			mul_color(t_color color, t_color light, double factor);
t_color			scale_color(t_color color, double factor);

t_color_linear		srgb_to_linear_color(t_color color);
t_color				linear_to_srgb_approx(t_color_linear color);

t_color_linear	color_add_linear(t_color_linear a, t_color_linear b);
t_color_linear	color_multiply_linear(t_color_linear a, t_color_linear b);
t_color_linear	color_scale_linear(t_color_linear c, double factor);
t_color_linear	color_lerp_linear(t_color_linear a, t_color_linear b, double t);




#endif
