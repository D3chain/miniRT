/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_op_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 22:57:46 by fox               #+#    #+#             */
/*   Updated: 2026/01/13 23:21:23 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

__attribute__((const, hot))
t_real	dot(t_real3 a, t_real3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

__attribute__((const, hot))
t_real	sqdot(t_real3 v)
{
	return (dot(v, v));
}

__attribute__((pure, hot))
t_real3	normalize3(t_real3 v)
{
	const t_real	norm = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	
	return ((t_real3){v.x / norm, v.y / norm, v.z / norm});
}

__attribute__((const, hot))
t_real3 reflect(t_real3 incident, t_real3 normal)
{
	const t_real		dot_product = dot(incident, normal);
	const t_real3		scaled_normal = fmul3(normal, 2.0 * dot_product);
	
	return (minus3(incident, scaled_normal));
}

__attribute__((const, hot))
t_real3	project(t_real3 origin, t_real3 dir, t_real dst)
{
	return (plus3(origin, fmul3(dir, dst)));
}
