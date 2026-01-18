/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_effect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 10:49:32 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/18 22:26:40 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

__attribute__((always_inline))
static inline t_real fresnel_schlick(struct s_scene *scene, t_phong *phong)
{
	const t_real	value = FLT_1 - fmax(0.0, dot(phong->N, phong->V));
	t_real			f0;

	f0 = (phong->hit_info.material.ior - scene->environment_ior) / 
		(phong->hit_info.material.ior + scene->environment_ior);
	f0 *= f0;	
	return (f0 + (FLT_1 - f0) * value * value * value * value * value);
}

static inline void	ambient_light(struct s_scene *scene, t_phong *phong)
{
	phong->ambient_light_color_linear = mul_color_linear(
		phong->hit_info.material.color_linear,
		scene->ambient.color_linear,
		scene->ambient.ratio * phong->hit_info.material.ka
	);
	phong->final_color_linear = phong->ambient_light_color_linear;
}

static inline void	diffuse_specular_light(struct s_scene *scene, 
		t_phong *phong, int light_index)
{
	if (!phong->in_shadow)
	{
		phong->NdotL = fmax(0.0, dot(phong->N, phong->L));
		phong->diffuse_color_linear = mul_color_linear(
			phong->hit_info.material.color_linear,
			scene->light[light_index].color_linear,
			phong->NdotL * scene->light[light_index].ratio * 
			phong->hit_info.material.kd
		);
		phong->R = reflect(fmul3(phong->L, -1.0), phong->N);
		phong->RdotV = fmax(0.0, dot(phong->R, phong->V));
		phong->fresnel_factor = fresnel_schlick(scene, phong);
		phong->specular_factor = pow(phong->RdotV, phong->hit_info.material.shininess);
		phong->specular_color_linear = scale_color_linear(
			scene->light[light_index].color_linear,
			phong->specular_factor * phong->hit_info.material.ks * 
			phong->fresnel_factor * scene->light[light_index].ratio
		);
		phong->final_color_linear = add_color_linear(
			phong->final_color_linear, phong->diffuse_color_linear);
		phong->final_color_linear = add_color_linear(
			phong->final_color_linear, phong->specular_color_linear);		
	}	
}

static inline void	collision(struct s_scene *scene, t_phong *phong, 
		t_hit_info *hit_info, int light_index)
{
	phong->hit_info = *hit_info;
	phong->P = phong->hit_info.hit_point;
	phong->N = normalize3(phong->hit_info.normal);
	phong->V = normalize3(minus3(scene->camera.focal_center, phong->P));
	phong->L = normalize3(minus3(scene->light[light_index].coord, phong->P));
	phong->shadow_ray.origin = plus3(phong->P, fmul3(phong->N, 1 + EPSILON));
	phong->shadow_ray.dir = phong->L;
	phong->light_distance = norm3(
		minus3(scene->light[light_index].coord, phong->P));
	phong->in_shadow = bvh_any_hit(
		scene->bvh_root, &phong->shadow_ray, phong->light_distance);
	if (!phong->in_shadow)
		phong->in_shadow = elem_inf_any_hit(
			scene, &phong->shadow_ray, phong->light_distance);
}

__attribute__((hot))
t_color_linear phong_effect(struct s_scene *scene, t_hit_info *hit_info)
{
	t_phong phong;
	int		i;

	// phong = (t_phong){0};
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
