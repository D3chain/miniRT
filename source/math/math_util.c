/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:02:05 by echatela          #+#    #+#             */
/*   Updated: 2025/12/08 17:45:46 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// __attribute__((const, hot))
double	dot(t_double3 a, t_double3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_double3	dot3(t_double3 a, t_double3 b)
{
	t_double3	res;

	res.x = a.x * b.x;
	res.y = a.y * b.y;
	res.z = a.z * b.z;
	return (res);
}

t_double3	plus3(t_double3 a, t_double3 b)
{
	t_double3	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

t_double3	minus3(t_double3 a, t_double3 b)
{
	t_double3	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

t_double3	mul3(t_double3 a, double factor)
{
	t_double3	res;

	res.x = a.x * factor;
	res.y = a.y * factor;
	res.z = a.z * factor;
	return (res);
}


t_double3	cross3(t_double3 a, t_double3 b)
{
	return ((t_double3){
		a.y * b.z - a.z * b.y, 
		a.z * b.x - a.x * b.z, 
		a.x * b.y - a.y * b.x});
}

t_double3	vector_normalise(t_double3 v)
{
	const double	norm = sqrt(pow(v.x, 2.0) + pow(v.y, 2.0) + pow(v.z, 2.0));
	return ((t_double3){v.x / norm, v.y / norm, v.z / norm});
}

double	sqdot(t_double3 v)
{
	return (dot(v, v));
}

t_double3	project(const t_double3 origin, const t_double3 dir, const double dst)
{
	return (plus3(origin, mul3(dir, dst)));
}

t_double3	orient_normal(t_double3 normal, t_double3 ray)
{
	if (dot(ray, normal) >= EPSILON)
		return (mul3(normal, -1.0));
	return (normal);
}
