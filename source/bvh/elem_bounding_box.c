/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_bounding_box.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:24:19 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/21 12:32:49 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_boundbox	cone_box(t_shape *elem)
{
	t_real	radius;
	t_real3	axis;
	t_real3	apex;
	t_real3	base;
	t_real3	ext;

	radius = elem->u.cone.radius;
	axis = elem->u.cone.axis;
	apex = elem->u.cone.apex;
	base = elem->u.cone.base;
	ext.x = radius * sqrt(1.0 - axis.x * axis.x);
	ext.y = radius * sqrt(1.0 - axis.y * axis.y);
	ext.z = radius * sqrt(1.0 - axis.z * axis.z);
	return ((t_boundbox){
		.beg.x = fmin(base.x, apex.x) - ext.x,
		.beg.y = fmin(base.y, apex.y) - ext.y,
		.beg.z = fmin(base.z, apex.z) - ext.z,
		.end.x = fmax(base.x, apex.x) + ext.x,
		.end.y = fmax(base.y, apex.y) + ext.y,
		.end.z = fmax(base.z, apex.z) + ext.z});
}

static t_boundbox	cylinder_box(t_shape *elem)
{
	t_real	radius;
	t_real3	axis;
	t_real3	p1;
	t_real3	p2;
	t_real3	ext;

	radius = elem->u.cylinder.radius;
	axis = elem->u.cylinder.axis;
	p1 = elem->u.cylinder.p1;
	p2 = elem->u.cylinder.p2;
	ext.x = radius * sqrt(1.0 - axis.x * axis.x);
	ext.y = radius * sqrt(1.0 - axis.y * axis.y);
	ext.z = radius * sqrt(1.0 - axis.z * axis.z);
	return ((t_boundbox){
		.beg.x = fmin(p1.x, p2.x) - ext.x,
		.beg.y = fmin(p1.y, p2.y) - ext.y,
		.beg.z = fmin(p1.z, p2.z) - ext.z,
		.end.x = fmax(p1.x, p2.x) + ext.x,
		.end.y = fmax(p1.y, p2.y) + ext.y,
		.end.z = fmax(p1.z, p2.z) + ext.z});
}

static t_boundbox	sphere_box(t_shape *elem)
{
	t_real3	coord;
	t_real	radius;

	coord = elem->u.sphere.coord;
	radius = elem->u.sphere.radius;
	return ((t_boundbox){
		.beg.x = coord.x - radius,
		.beg.y = coord.y - radius,
		.beg.z = coord.z - radius,
		.end.x = coord.x + radius,
		.end.y = coord.y + radius,
		.end.z = coord.z + radius});
}

t_boundbox	elem_bounding_box(t_shape *elem)
{
	int	type;

	type = elem->type;
	if (type == SPHERE)
		return (sphere_box(elem));
	else if (type == CYLINDER)
		return (cylinder_box(elem));
	else if (type == CONE)
		return (cone_box(elem));
	else
		return ((t_boundbox){
			.beg.x = -INFINITY,
			.beg.y = -INFINITY,
			.beg.z = -INFINITY,
			.end.x = INFINITY,
			.end.y = INFINITY,
			.end.z = INFINITY});
}
