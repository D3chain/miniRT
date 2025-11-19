/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:02:05 by echatela          #+#    #+#             */
/*   Updated: 2025/11/19 16:14:48 by cgajean          ###   ########.fr       */
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

t_double3	vector_normalise(t_double3 v)
{
	const double	norm = sqrt(pow(v.x, 2.0) + pow(v.y, 2.0) + pow(v.z, 2.0));
	return ((t_double3){v.x / norm, v.y / norm, v.z / norm});
}

double	sqdot(t_double3 v)
{
	return (dot(v, v));
}
