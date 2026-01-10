/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_effect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 10:49:32 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/10 13:40:39 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline void	ambient_light(struct s_scene *scene, t_phong *phong)
{
	phong->ambient_light_color_linear = mul_color_linear(
		phong->hit_info.material.color_linear,
		scene->ambient.color_linear,
		scene->ambient.ratio * phong->hit_info.material.ka
	);
	phong->final_color_linear = phong->ambient_light_color_linear;
}

static inline void	diffuse_specular_light(struct s_scene *scene, t_phong *phong, int light_index)
{
	if (!phong->in_shadow)
	{
		phong->NdotL = fmax(0.0, dot(phong->N, phong->L));
		phong->diffuse_color_linear = mul_color_linear(
			phong->hit_info.material.color_linear,
			scene->light[light_index].color_linear,
			phong->NdotL * scene->light[light_index].ratio * phong->hit_info.material.kd		// modifie light ici de facon temporaire -> contre .
		);

		phong->R = reflect(mul3(phong->L, -1.0), phong->N);
		phong->RdotV = fmax(0.0, dot(phong->R, phong->V));

		phong->fresnel_factor = fresnel_schlick(scene, phong->hit_info.material, phong->N, phong->V);
			
		phong->specular_factor = pow(phong->RdotV, phong->hit_info.material.shininess);
		phong->specular_color_linear = scale_color_linear(
			scene->light[light_index].color_linear,
			phong->specular_factor * phong->hit_info.material.ks * phong->fresnel_factor * scene->light[light_index].ratio		// modifie light ici de facon temporaire -> contre .
		);
		phong->final_color_linear = color_add_linear(phong->final_color_linear, phong->diffuse_color_linear);
		phong->final_color_linear = color_add_linear(phong->final_color_linear, phong->specular_color_linear);		
	}	
}

static inline void	collision(struct s_scene *scene, t_phong *phong, t_hit_info *hit_info, int light_index)
{
	phong->hit_info = *hit_info;
	phong->P = phong->hit_info.hit_point;
	phong->N = normalize3(phong->hit_info.normal);
	phong->V = normalize3(minus3(scene->camera.focal_center, phong->P));
	phong->L = normalize3(minus3(scene->light[light_index].coord, phong->P));
	phong->shadow_ray.origin = plus3(phong->P, mul3(phong->N, 1 + EPSILON));
	phong->shadow_ray.dir = phong->L;
	
	phong->light_distance = norm3(minus3(scene->light[light_index].coord, phong->P));
	
	phong->shadow_hit = bvh_traverse(scene->bvh_root, &phong->shadow_ray);
	// phong->shadow_hit = ray_hit(&phong->shadow_ray, scene->elems, scene->n_elem);
	
	phong->in_shadow = bvh_any_hit(scene->bvh_root, &phong->shadow_ray, phong->light_distance);

	// phong->in_shadow = (phong->shadow_hit.did_hit && phong->shadow_hit.dst < phong->light_distance - EPSILON);
}

t_color_linear phong_effect(struct s_scene *scene, t_hit_info *hit_info)
{
	t_phong			phong;
	t_color_linear	final_color_linear;
	int				i;

	ft_bzero(&final_color_linear, sizeof(final_color_linear));
	i = 0;
	
	while (i < scene->n_light)
	{
		ft_bzero(&phong, sizeof(phong));
		collision(scene, &phong, hit_info, i);
		ambient_light(scene, &phong);
		diffuse_specular_light(scene, &phong, i);
		if (i++)
			final_color_linear = color_add_linear(final_color_linear, phong.final_color_linear);
		else
			final_color_linear = phong.final_color_linear;
	}

	return (final_color_linear);
}
