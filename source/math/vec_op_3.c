/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_op_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:20:56 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/20 19:13:33 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

__attribute__((const))
t_real3	orient_normal(t_real3 normal, t_real3 ray)
{
	if (dot(ray, normal) >= EPSILON)
		return (fmul3(normal, -FLT_1));
	return (normal);
}

__attribute__((pure))
t_real	norm3(t_real3 vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

__attribute__((always_inline, const))
inline t_real	dot(t_real3 a, t_real3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

__attribute__((const))
t_real	sqdot(t_real3 v)
{
	return (dot(v, v));
}
