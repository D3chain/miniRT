/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:02:05 by echatela          #+#    #+#             */
/*   Updated: 2025/11/18 11:03:01 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

__attribute__((const, hot))
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
