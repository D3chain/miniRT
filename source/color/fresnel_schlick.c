/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fresnel_schlick.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 00:41:18 by fox               #+#    #+#             */
/*   Updated: 2025/12/17 10:56:24 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double ior_to_f0(struct s_scene *scene, t_material *mat)
{
    double ratio = (mat->ior - scene->environment_ior) / (mat->ior + scene->environment_ior);
    return (ratio * ratio);
}

double fresnel_schlick(struct s_scene *scene, t_material mat, t_double3 N, t_double3 V)
{
	const double	value = 1 - fmax(0.0, dot(N, V));
	const double	f0 = ior_to_f0(scene, &mat);
	return (f0 + (1.0 - f0) * value * value * value * value * value);
}
