/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_op_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 22:57:46 by fox               #+#    #+#             */
/*   Updated: 2026/01/16 19:02:54 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

__attribute__((const))
t_real3	fplus3(t_real3 a, t_real factor)
{
	return ((t_real3){
		.x = a.x + factor,
		.y = a.y + factor,
		.z = a.z + factor
	});
}

__attribute__((const))
t_real3	fmul3(t_real3 a, t_real factor)
{
	return ((t_real3){
		.x = a.x * factor,
		.y = a.y * factor,
		.z = a.z * factor
	});
}




__attribute__((const))
t_real3 reflect(t_real3 incident, t_real3 normal)
{
	const t_real		dot_product = dot(incident, normal);
	const t_real3		scaled_normal = fmul3(normal, 2.0 * dot_product);
	
	return (minus3(incident, scaled_normal));
}

__attribute__((const))
t_real3	project(t_real3 origin, t_real3 dir, t_real dst)
{
	return (plus3(origin, fmul3(dir, dst)));
}
