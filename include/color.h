/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 16:38:48 by cgajean           #+#    #+#             */
/*   Updated: 2025/12/17 11:57:15 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "minirt.h"

# define WHITE	0xFFFFFF
# define BLACK	0x0
# define RED	0xFF0000
# define GREEN	0xFF00
# define BLUE 	0xFF

typedef union u_color			t_color;
typedef struct s_color_linear	t_color_linear;
typedef struct s_double3		t_double3;
typedef struct s_material		t_material;
struct s_app;
struct s_scene;

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

/*	sRGB colors	*/

t_color				color_add(t_color color1, t_color color2);
t_color				mul_color(t_color color, t_color light, double factor);
t_color				scale_color(t_color color, double factor);


/*	Linear colors	*/

double				rgb_to_linear(double channel);
t_color_linear		srgb_to_linear_color(t_color color);

double				linear_to_srgb(double channel);
t_color 			linear_to_srgb_color(t_color_linear linear);

t_color_linear 		color_add_linear(t_color_linear a, t_color_linear b);
t_color_linear 		scale_color_linear(t_color_linear c, double factor);
t_color_linear 		mul_color_linear(t_color_linear a, t_color_linear b, double factor);

/*	Tone mapping	*/
t_color_linear		tone_map_clamp(t_color_linear c);
t_color_linear		tone_map_reinhard(t_color_linear c);
t_color_linear		tone_map_aces(t_color_linear x);
t_color_linear		tone_map_luminance(t_color_linear c);


double				fresnel_schlick(struct s_scene *scene, t_material mat, t_double3 N, t_double3 V);


#endif
