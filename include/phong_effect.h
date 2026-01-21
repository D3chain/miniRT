/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_effect.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:19:14 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/21 17:13:05 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONG_EFFECT_H
# define PHONG_EFFECT_H

# include "minirt_typedef.h"
# include "types.h"

# define WHITE	0xFFFFFF
# define BLACK	0x0
# define RED	0xFF0000
# define GREEN	0xFF00
# define BLUE 	0xFF

struct s_phong_effect
{
	t_ray		primary_ray;
	t_ray		shadow_ray;
	t_hit_info	hit_info;
	t_hit_info	shadow_hit;

	t_real3		n;	
	t_real3		p;
	t_real3		v;
	t_real3		l;
	t_real3		r;

	t_real		n_dot_l;
	t_real		r_dot_v;

	t_color_lin	ambient_color_lin;
	t_color_lin	diffuse_color_linear;
	t_color_lin	specular_color_linear;
	t_color_lin	final_color_linear;

	t_real		light_distance;

	t_real		fresnel_factor;
	t_real		specular_factor;

	bool		in_shadow;
};

t_color_lin	phong_effect(t_scene *scene, t_hit_info *hit_info);

#endif
