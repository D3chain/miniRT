/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_aabb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 13:32:41 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/14 13:49:28 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

struct s_intersect
{
	t_real	nearest;
	t_real	farthest;
};

struct s_aabb_var
{
	t_real3			t_lo;
	t_real3			t_hi;
	t_real3			t_close;
	t_real3			t_far;
	t_real			t_near;
};

__attribute__((hot))
bool	collision_aabb_base(t_bvh_base *base, t_ray *ray)
{
	struct s_aabb_var	v;
	t_real				t_far_final;

	v.t_lo.x = (base->bbox.beg.x - ray->origin.x) / ray->dir.x;
	v.t_lo.y = (base->bbox.beg.y - ray->origin.y) / ray->dir.y;
	v.t_lo.z = (base->bbox.beg.z - ray->origin.z) / ray->dir.z;
	v.t_hi.x = (base->bbox.end.x - ray->origin.x) / ray->dir.x;
	v.t_hi.y = (base->bbox.end.y - ray->origin.y) / ray->dir.y;
	v.t_hi.z = (base->bbox.end.z - ray->origin.z) / ray->dir.z;
	v.t_close.x = fmin(v.t_lo.x, v.t_hi.x);
	v.t_close.y = fmin(v.t_lo.y, v.t_hi.y);
	v.t_close.z = fmin(v.t_lo.z, v.t_hi.z);
	v.t_far.x = fmax(v.t_lo.x, v.t_hi.x);
	v.t_far.y = fmax(v.t_lo.y, v.t_hi.y);
	v.t_far.z = fmax(v.t_lo.z, v.t_hi.z);
	v.t_near = fmax(fmax(v.t_close.x, v.t_close.y), v.t_close.z);
	t_far_final = fmin(fmin(v.t_far.x, v.t_far.y), v.t_far.z);
	if (v.t_near > t_far_final)
		return (false);
	if (t_far_final < 0)
		return (false);
	return (true);
}

__attribute__((hot))
bool	collision_aabb(t_bvh_node *node, t_ray *ray)
{
	struct s_aabb_var	v;
	struct s_intersect	t;

	v.t_lo.x = (node->bbox.beg.x - ray->origin.x) / ray->dir.x;
	v.t_lo.y = (node->bbox.beg.y - ray->origin.y) / ray->dir.y;
	v.t_lo.z = (node->bbox.beg.z - ray->origin.z) / ray->dir.z;
	v.t_hi.x = (node->bbox.end.x - ray->origin.x) / ray->dir.x;
	v.t_hi.y = (node->bbox.end.y - ray->origin.y) / ray->dir.y;
	v.t_hi.z = (node->bbox.end.z - ray->origin.z) / ray->dir.z;
	v.t_close.x = fmin(v.t_lo.x, v.t_hi.x);
	v.t_close.y = fmin(v.t_lo.y, v.t_hi.y);
	v.t_close.z = fmin(v.t_lo.z, v.t_hi.z);
	v.t_far.x = fmax(v.t_lo.x, v.t_hi.x);
	v.t_far.y = fmax(v.t_lo.y, v.t_hi.y);
	v.t_far.z = fmax(v.t_lo.z, v.t_hi.z);
	t.nearest = fmax(fmax(v.t_close.x, v.t_close.y), v.t_close.z);
	t.farthest = fmin(fmin(v.t_far.x, v.t_far.y), v.t_far.z);
	if (t.nearest > t.farthest)
		return (false);
	if (t.farthest < 0)
		return (false);
	return (true);
}
