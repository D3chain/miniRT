/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_op_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 22:54:48 by fox               #+#    #+#             */
/*   Updated: 2026/01/14 13:07:04 by cgajean          ###   ########.fr       */
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
t_real3	fmul3(t_real3 a, t_real factor)
{
	return ((t_real3){
		.x = a.x * factor,
		.y = a.y * factor,
		.z = a.z * factor
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
