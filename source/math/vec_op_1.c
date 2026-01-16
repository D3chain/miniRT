/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_op_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 22:54:48 by fox               #+#    #+#             */
/*   Updated: 2026/01/16 19:01:24 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

__attribute__((const))
t_real3	plus3(t_real3 a, t_real3 b)
{
	return ((t_real3){
		.x = a.x + b.x,
		.y = a.y + b.y,
		.z = a.z + b.z
	});
}

__attribute__((const))
t_real3	minus3(t_real3 a, t_real3 b)
{
	return ((t_real3){
		.x = a.x - b.x,
		.y = a.y - b.y,
		.z = a.z - b.z
	});
}

__attribute__((const))
t_real3	vmul3(t_real3 a, t_real3 b)
{
	return ((t_real3){
		.x = a.x * b.x,
		.y = a.y * b.y,
		.z = a.z * b.z
	});
}

__attribute__((const))
t_real3	cross3(t_real3 a, t_real3 b)
{
	return ((t_real3){
		a.y * b.z - a.z * b.y, 
		a.z * b.x - a.x * b.z, 
		a.x * b.y - a.y * b.x
	});
}

__attribute__((pure))
t_real3	normalize3(t_real3 v)
{
	const t_real	norm = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	
	return ((t_real3){v.x / norm, v.y / norm, v.z / norm});
}
