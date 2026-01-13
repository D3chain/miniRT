/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 16:38:48 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/13 15:19:42 by cgajean          ###   ########.fr       */
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
	
	t_double3	N;	
	t_double3	P;	/*	point d'impact							*/
	t_double3	V;	/*	direction vers la camera				*/
	t_double3	L;	/*	direction vers la lumiere				*/
	t_double3	R;	/*	direction des reflexions (speculaire)	*/

	double		NdotL;
	double		RdotV;
	
	t_color	i_a;	/*	intensite ambient calculee		*/
	t_color	i_d;	/*	intensite diffuse calculee		*/
	t_color	i_s;	/*	intensite speculaire calculee	*/

	t_color_linear	ambient_light_color_linear;
	t_color_linear	light_color_linear;

	t_color_linear	diffuse_color_linear;
	t_color_linear	specular_color_linear;

	t_color_linear	final_color_linear;


	double	light_distance;
	
	double	fresnel_factor;
	double	specular_factor;

	bool	in_shadow;
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

t_color_linear 		phong_effect(struct s_scene *scene, t_hit_info *hit_info);
t_color_linear		basic_render(struct s_app *app, double x, double y);
t_color_linear		antialiasing(struct s_app *app, double x, double y);

#endif
