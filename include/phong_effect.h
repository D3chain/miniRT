/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_effect.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 16:38:48 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/13 16:46:19 by cgajean          ###   ########.fr       */
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
	
	t_real3	N;	
	t_real3	P;
	t_real3	V;
	t_real3	L;
	t_real3	R;

	t_real		NdotL;
	t_real		RdotV;
	
	t_color	i_a;
	t_color	i_d;
	t_color	i_s;

	t_color_linear	ambient_light_color_linear;
	t_color_linear	light_color_linear;

	t_color_linear	diffuse_color_linear;
	t_color_linear	specular_color_linear;

	t_color_linear	final_color_linear;


	t_real	light_distance;
	
	t_real	fresnel_factor;
	t_real	specular_factor;

	bool	in_shadow;
};

/*	sRGB colors	*/

t_color				color_add(t_color color1, t_color color2);
t_color				mul_color(t_color color, t_color light, t_real factor);
t_color				scale_color(t_color color, t_real factor);

/*	Linear colors	*/

t_real				rgb_to_linear(t_real channel);
t_color_linear		srgb_to_linear_color(t_color color);

t_real				linear_to_srgb(t_real channel);
t_color 			linear_to_srgb_color(t_color_linear linear);

t_color_linear 		color_add_linear(t_color_linear a, t_color_linear b);
t_color_linear 		scale_color_linear(t_color_linear c, t_real factor);
t_color_linear 		mul_color_linear(t_color_linear a, t_color_linear b, t_real factor);

/*	Tone mapping	*/
t_color_linear		tone_map_clamp(t_color_linear c);
t_color_linear		tone_map_reinhard(t_color_linear c);
t_color_linear		tone_map_aces(t_color_linear x);
t_color_linear		tone_map_luminance(t_color_linear c);

t_real				fresnel_schlick(struct s_scene *scene, t_material mat, t_real3 N, t_real3 V);

t_color_linear 		phong_effect(struct s_scene *scene, t_hit_info *hit_info);
t_color_linear		basic_render(struct s_app *app, t_real x, t_real y);
t_color_linear		antialiasing(struct s_app *app, t_real x, t_real y);

#endif
