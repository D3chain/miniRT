/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_effect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 10:49:32 by cgajean           #+#    #+#             */
/*   Updated: 2025/12/17 14:05:36 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline t_double3 reflect(t_double3 incident, t_double3 normal)
{
	// Formule : R = I - 2(I·N)N
	const double		dot_product = dot(incident, normal);
	const t_double3		scaled_normal = mul3(normal, 2.0 * dot_product);
	return (minus3(incident, scaled_normal));
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

static inline void	diffuse_specular_light(struct s_scene *scene, t_phong *phong)
{
	if (!phong->in_shadow)
	{
		phong->NdotL = fmax(0.0, dot(phong->N, phong->L));
		phong->diffuse_color_linear = mul_color_linear(
			phong->hit_info.material.color_linear,
			scene->light.color_linear,
			phong->NdotL * scene->light.ratio * phong->hit_info.material.kd
		);

		phong->R = reflect(mul3(phong->L, -1.0), phong->N);
		phong->RdotV = fmax(0.0, dot(phong->R, phong->V));

		phong->fresnel_factor = fresnel_schlick(scene, phong->hit_info.material, phong->N, phong->V);
			
		phong->specular_factor = pow(phong->RdotV, phong->hit_info.material.shininess);
		phong->specular_color_linear = scale_color_linear(
			scene->light.color_linear,
			phong->specular_factor * phong->hit_info.material.ks * phong->fresnel_factor
		);
		phong->final_color_linear = color_add_linear(phong->final_color_linear, phong->diffuse_color_linear);
		phong->final_color_linear = color_add_linear(phong->final_color_linear, phong->specular_color_linear);		
	}	
}

static inline void	collision(struct s_scene *scene, t_phong *phong)
{
	phong->P = phong->hit_info.hit_point;
	phong->N = normalize3(phong->hit_info.normal);
	phong->V = normalize3(minus3(scene->camera.focal_center, phong->P));
	phong->L = normalize3(minus3(scene->light.coord, phong->P));
	
	phong->shadow_ray.origin = plus3(phong->P, mul3(phong->N, 1 + EPSILON));
	phong->shadow_ray.dir = phong->L;
	
	phong->light_distance = norm3(minus3(scene->light.coord, phong->P));
	phong->shadow_hit = ray_hit(&phong->shadow_ray, scene->elems, scene->n_elem);
	
	phong->in_shadow = (phong->shadow_hit.did_hit && phong->shadow_hit.dst < phong->light_distance - EPSILON);
}

void phong_effect(struct s_scene *scene, t_phong *phong)
{
	collision(scene, phong);
	ambient_light(scene, phong);
	diffuse_specular_light(scene, phong);	

	phong->final_color_linear = tone_map_aces(phong->final_color_linear);
	// phong->final_color_linear = tone_map_reinhard(phong->final_color_linear);
	// phong->final_color_linear = tone_map_luminance(phong->final_color_linear);
	// phong->final_color_linear = tone_map_clamp(phong->final_color_linear);
	
	phong->final_color = linear_to_srgb_color(phong->final_color_linear);
}
