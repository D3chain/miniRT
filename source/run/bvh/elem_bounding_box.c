/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb_volume.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 21:24:36 by fox               #+#    #+#             */
/*   Updated: 2026/01/10 11:36:36 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_boundbox	cone_box(struct s_elem *elem)
{
	double			radius;
	t_double3		axis;
	t_double3		apex;
	t_double3		base;
	t_double3		ext;

	radius = elem->u.cone.radius;
	axis = elem->u.cone.axis;
	base = elem->u.cone.p1;
	apex = elem->u.cone.p2;
	
	ext.x = radius * sqrt(1.0 - axis.x * axis.x);
	ext.y = radius * sqrt(1.0 - axis.y * axis.y);
	ext.z = radius * sqrt(1.0 - axis.z * axis.z);
	
	return ((t_boundbox) {
		.beg.x = fmin(base.x - ext.x, apex.x),
		.beg.y = fmin(base.y - ext.y, apex.y),
		.beg.z = fmin(base.z - ext.z, apex.z),
		.end.x = fmax(base.x + ext.x, apex.x),
		.end.y = fmax(base.y + ext.y, apex.y),
		.end.z = fmax(base.z + ext.z, apex.z),
	});
}

static t_boundbox	cylinder_box(struct s_elem *elem)
{
	double				radius;
	t_double3			axis;
	t_double3			p1;
	t_double3			p2;
	t_double3			ext;

	radius = elem->u.cylinder.radius;
	axis = elem->u.cylinder.axis;
	p1 = elem->u.cylinder.p1;
	p2 = elem->u.cylinder.p2;

	ext.x = radius * sqrt(1.0 - axis.x * axis.x);
	ext.y = radius * sqrt(1.0 - axis.y * axis.y);
	ext.z = radius * sqrt(1.0 - axis.z * axis.z);

	return ((t_boundbox) {
		.beg.x = fmin(p1.x, p2.x) - ext.x,
		.beg.y = fmin(p1.y, p2.y) - ext.y,
		.beg.z = fmin(p1.z, p2.z) - ext.z,
	
		.end.x = fmax(p1.x, p2.x) + ext.x,
		.end.y = fmax(p1.y, p2.y) + ext.y,
		.end.z = fmax(p1.z, p2.z) + ext.z,
	});
}

static t_boundbox	sphere_box(struct s_elem *elem)
{
	t_point3	coord;
	double		radius;

	coord = elem->u.sphere.coord;
	radius = elem->u.sphere.radius;
	return ((t_boundbox) {
		.beg.x = coord.x - radius,
		.beg.y = coord.y - radius,
		.beg.z = coord.z - radius,
		.end.x = coord.x + radius,
		.end.y = coord.y + radius,
		.end.z = coord.z + radius,		
	});
}

t_boundbox	elem_bounding_box(struct s_elem *elem)
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
		return ((t_boundbox){{INFINITY, INFINITY, INFINITY}, 
		.beg.x = -INFINITY,
		.beg.y = -INFINITY,
		.beg.z = -INFINITY,
		.end.x = INFINITY,
		.end.y = INFINITY,
		.end.z = INFINITY,		
	});
}
