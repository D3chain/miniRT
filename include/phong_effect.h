/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_effect.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:19:14 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/19 17:30:24 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <stdint.h>

# define WHITE	0xFFFFFF
# define BLACK	0x0
# define RED	0xFF0000
# define GREEN	0xFF00
# define BLUE 	0xFF

struct s_app;
struct s_scene;

struct s_phong_effect
{
	t_ray		primary_ray;
	t_ray		shadow_ray;
	t_hit_info	hit_info;
	t_hit_info	shadow_hit;
	
	t_real3		N;	
	t_real3		P;
	t_real3		V;
	t_real3		L;
	t_real3		R;

	t_real		NdotL;
	t_real		RdotV;

	t_color_linear	ambient_color_linear;
	t_color_linear	diffuse_color_linear;
	t_color_linear	specular_color_linear;
	t_color_linear	final_color_linear;

	t_real	light_distance;
	
	t_real	fresnel_factor;
	t_real	specular_factor;

	bool	in_shadow;
};

/*	Linear colors	*/

t_real				rgb_to_linear(t_real channel);
t_color_linear		srgb_to_linear_color(t_color color);

// t_real				linear_to_srgb(t_real channel);
t_color 			linear_to_srgb_color(t_color_linear linear);

t_color_linear 		add_color_linear(t_color_linear a, t_color_linear b);
t_color_linear 		scale_color_linear(t_color_linear c, t_real factor);
t_color_linear 		mul_color_linear(t_color_linear a, t_color_linear b, t_real factor);

t_color_linear 		phong_effect(struct s_scene *scene, t_hit_info *hit_info);
t_color_linear		basic_render(struct s_app *app, t_real x, t_real y);
t_color_linear		antialiasing(struct s_app *app, t_real x, t_real y);

#endif
