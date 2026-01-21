/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_effect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:24:03 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/21 17:12:03 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

__attribute__((always_inline))
static inline t_real	fresnel_schlick(t_scene *scene, t_phong *phong)
{
	const t_real	value = FLT_1 - fmax(0.0, dot(phong->n, phong->v));
	t_real			f0;

	f0 = (phong->hit_info.material.ior - scene->environment_ior) \
		/ (phong->hit_info.material.ior + scene->environment_ior);
	f0 *= f0;
	return (f0 + (FLT_1 - f0) * value * value * value * value * value);
}

static inline void	ambient_light(t_scene *scene, t_phong *phong)
{
	phong->ambient_color_lin = mul_color_linear(\
		phong->hit_info.material.color_linear, \
		scene->ambient.color_linear, \
		scene->ambient.ratio * phong->hit_info.material.ka \
	);
	phong->final_color_linear = phong->ambient_color_lin;
}

static inline void	diffuse_specular_light(t_scene *scene, \
		t_phong *phong, int light_index)
{
	if (!phong->in_shadow)
	{
		phong->n_dot_l = fmax(0.0, dot(phong->n, phong->l));
		phong->diffuse_color_linear = mul_color_linear(\
			phong->hit_info.material.color_linear, \
			scene->light[light_index].color_linear, \
			phong->n_dot_l * scene->light[light_index].ratio \
			* phong->hit_info.material.kd \
		);
		phong->r = reflect(fmul3(phong->l, -1.0), phong->n);
		phong->r_dot_v = fmax(0.0, dot(phong->r, phong->v));
		phong->fresnel_factor = fresnel_schlick(scene, phong);
		phong->specular_factor = \
			pow(phong->r_dot_v, phong->hit_info.material.shininess);
		phong->specular_color_linear = scale_color_linear(\
			scene->light[light_index].color_linear, \
			phong->specular_factor * phong->hit_info.material.ks \
			* phong->fresnel_factor * scene->light[light_index].ratio \
		);
		phong->final_color_linear = add_color_linear(\
			phong->final_color_linear, phong->diffuse_color_linear);
		phong->final_color_linear = add_color_linear(\
			phong->final_color_linear, phong->specular_color_linear);
	}
}

static inline void	collision(t_scene *scene, t_phong *phong, \
		t_hit_info *hit_info, int light_index)
{
	phong->hit_info = *hit_info;
	phong->p = phong->hit_info.hit_point;
	phong->n = normalize3(phong->hit_info.normal);
	phong->v = normalize3(minus3(scene->camera.focal_center, phong->p));
	phong->l = normalize3(minus3(scene->light[light_index].coord, phong->p));
	phong->shadow_ray.origin = plus3(phong->p, fmul3(phong->n, 1 + EPSILON));
	phong->shadow_ray.dir = phong->l;
	phong->light_distance = norm3(\
		minus3(scene->light[light_index].coord, phong->p));
	phong->in_shadow = bvh_any_hit(\
		scene->bvh_root, &phong->shadow_ray, phong->light_distance);
	if (!phong->in_shadow)
		phong->in_shadow = elem_inf_any_hit(\
			scene, &phong->shadow_ray, phong->light_distance);
}

__attribute__((hot))
t_color_lin	phong_effect(t_scene *scene, t_hit_info *hit_info)
{
	t_phong	phong;
	int		i;

	phong.hit_info = *hit_info;
	ambient_light(scene, &phong);
	i = 0;
	while (i < scene->n_light)
	{
		collision(scene, &phong, hit_info, i);
		diffuse_specular_light(scene, &phong, i);
		i++;
	}
	return (phong.final_color_linear);
}
