/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_basic.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:15:41 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/13 17:47:08 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_BASIC_H
# define MATH_BASIC_H

# include "minirt.h"

struct s_sol2
{
	int		n;
	t_real	r1;
	t_real	r2;
};

__attribute__((pure, always_inline, hot))
static inline t_real3	plus3(t_real3 a, t_real3 b)
{	
	return ((t_real3){
		.x = a.x + b.x,
		.y = a.y + b.y,
		.z = a.z + b.z
	});
}

__attribute__((pure, always_inline, hot))
static inline t_real3	minus3(t_real3 a, t_real3 b)
{
	return ((t_real3){
		.x = a.x - b.x,
		.y = a.y - b.y,
		.z = a.z - b.z
	});
}

__attribute__((pure, always_inline, hot))
static inline t_real3	mul3(t_real3 a, t_real factor)
{
	return ((t_real3){
		.x = a.x * factor,
		.y = a.y * factor,
		.z = a.z * factor
	});
}

__attribute__((pure, always_inline, hot))
static inline t_real	dot(t_real3 a, t_real3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

__attribute__((pure, always_inline))
static inline t_real3	dot3(t_real3 a, t_real3 b)
{
	return ((t_real3){
		.x = a.x * b.x,
		.y = a.y * b.y,
		.z = a.z * b.z
	});
}

__attribute__((pure, always_inline))
static inline t_real3	cross3(t_real3 a, t_real3 b)
{
	return ((t_real3){
		a.y * b.z - a.z * b.y, 
		a.z * b.x - a.x * b.z, 
		a.x * b.y - a.y * b.x
	});
}

__attribute__((pure, hot))
static inline t_real3	normalize3(t_real3 v)
{
	const t_real	norm = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	
	return ((t_real3){v.x / norm, v.y / norm, v.z / norm});
}

__attribute__((pure, always_inline, hot))
static inline t_real	sqdot(t_real3 v)
{
	return (dot(v, v));
}

__attribute__((pure, always_inline, hot))
static inline t_real3	project(const t_real3 origin, const t_real3 dir, const t_real dst)
{
	return (plus3(origin, mul3(dir, dst)));
}

__attribute__((pure, hot))
static inline t_real3 reflect(t_real3 incident, t_real3 normal)
{
	const t_real		dot_product = dot(incident, normal);
	const t_real3		scaled_normal = mul3(normal, 2.0 * dot_product);
	
	return (minus3(incident, scaled_normal));
}

__attribute__((pure, hot))
static inline t_real3	orient_normal(t_real3 normal, t_real3 ray)
{
	if (dot(ray, normal) >= EPSILON)
		return (mul3(normal, -1.0));
	return (normal);
}

__attribute__((pure, hot))
static inline t_real	norm3(t_real3 vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}


__attribute__((pure, always_inline, hot))
static inline t_sol2	polynome2(t_real a, t_real b, t_real c)
{
	const t_real		dis = b * b - 4 * a * c;
	t_sol2				res;

	res.n = 0.0;
	res.r1 = 0.0;
	res.r2 = 0.0;
	if (dis < 0)
		res.n = 0;
	else if (dis == 0)
	{
		res.n = 1;
		res.r1 = (-b) / (2 * a);
	}
	else
	{
		res.n = 2;
		res.r1 = (-b - sqrt(dis)) / (2 * a);
		res.r2 = (-b + sqrt(dis)) / (2 * a);
	}
	return (res);
}

#endif
