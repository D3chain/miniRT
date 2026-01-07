/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:10:09 by fox               #+#    #+#             */
/*   Updated: 2026/01/07 17:13:54 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

inline t_color_linear	trace(struct s_scene *scene, const t_ray *ray)
{
	t_hit_info		hit_info;

	hit_info = ray_hit(ray, scene->elems, scene->n_elem);
	if (!hit_info.did_hit)
		return (srgb_to_linear_color((t_color){.value = BLACK}));
	return (phong_effect(scene, &hit_info));
}
