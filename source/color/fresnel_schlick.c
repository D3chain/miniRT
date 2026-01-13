/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fresnel_schlick.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 00:41:18 by fox               #+#    #+#             */
/*   Updated: 2026/01/13 16:48:26 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_real ior_to_f0(struct s_scene *scene, t_material *mat)
{
    t_real ratio = (mat->ior - scene->environment_ior) / (mat->ior + scene->environment_ior);
    return (ratio * ratio);
}

t_real fresnel_schlick(struct s_scene *scene, t_material mat, t_real3 N, t_real3 V)
{
	const t_real	value = 1 - fmax(0.0, dot(N, V));
	const t_real	f0 = ior_to_f0(scene, &mat);
	return (f0 + (1.0 - f0) * value * value * value * value * value);
}
