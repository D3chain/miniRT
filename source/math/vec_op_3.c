/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_op_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 23:06:11 by fox               #+#    #+#             */
/*   Updated: 2026/01/14 13:07:14 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

__attribute__((const))
t_real3	orient_normal(t_real3 normal, t_real3 ray)
{
	if (dot(ray, normal) >= EPSILON)
		return (fmul3(normal, -1.0));
	return (normal);
}

__attribute__((pure))
t_real	norm3(t_real3 vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}
