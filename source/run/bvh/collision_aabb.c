/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_aabb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 12:35:04 by fox               #+#    #+#             */
/*   Updated: 2026/01/14 12:46:48 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

struct s_intersect
{
	t_real	nearest;
	t_real	farthest;
};

__attribute__((hot))
bool	collision_aabb_base(t_bvh_base *base, t_ray *ray)
{
	t_real3			t_lo;
	t_real3			t_hi;
	t_real3			t_close;
	t_real3			t_far;
	t_real			t_near;
	t_real			t_far_final;

	t_lo.x = (base->bbox.beg.x - ray->origin.x) / ray->dir.x;
	t_lo.y = (base->bbox.beg.y - ray->origin.y) / ray->dir.y;
	t_lo.z = (base->bbox.beg.z - ray->origin.z) / ray->dir.z;
	t_hi.x = (base->bbox.end.x - ray->origin.x) / ray->dir.x;
	t_hi.y = (base->bbox.end.y - ray->origin.y) / ray->dir.y;
	t_hi.z = (base->bbox.end.z - ray->origin.z) / ray->dir.z;
	t_close.x = fmin(t_lo.x, t_hi.x);
	t_close.y = fmin(t_lo.y, t_hi.y);
	t_close.z = fmin(t_lo.z, t_hi.z);
	t_far.x = fmax(t_lo.x, t_hi.x);
	t_far.y = fmax(t_lo.y, t_hi.y);
	t_far.z = fmax(t_lo.z, t_hi.z);
	t_near = fmax(fmax(t_close.x, t_close.y), t_close.z);
	t_far_final = fmin(fmin(t_far.x, t_far.y), t_far.z);
	if (t_near > t_far_final)
		return (false);
	if (t_far_final < 0)
		return (false);
	return (true);
}

__attribute__((hot))
bool	collision_aabb(t_bvh_node *node, t_ray *ray)
{
	t_real3				t_lo;
	t_real3				t_hi;
	t_real3				t_close;
	t_real3				t_far;
	struct s_intersect	t;

	t_lo.x = (node->bbox.beg.x - ray->origin.x) / ray->dir.x;
	t_lo.y = (node->bbox.beg.y - ray->origin.y) / ray->dir.y;
	t_lo.z = (node->bbox.beg.z - ray->origin.z) / ray->dir.z;
	t_hi.x = (node->bbox.end.x - ray->origin.x) / ray->dir.x;
	t_hi.y = (node->bbox.end.y - ray->origin.y) / ray->dir.y;
	t_hi.z = (node->bbox.end.z - ray->origin.z) / ray->dir.z;
	t_close.x = fmin(t_lo.x, t_hi.x);
	t_close.y = fmin(t_lo.y, t_hi.y);
	t_close.z = fmin(t_lo.z, t_hi.z);
	t_far.x = fmax(t_lo.x, t_hi.x);
	t_far.y = fmax(t_lo.y, t_hi.y);
	t_far.z = fmax(t_lo.z, t_hi.z);
	t.nearest = fmax(fmax(t_close.x, t_close.y), t_close.z);
	t.farthest = fmin(fmin(t_far.x, t_far.y), t_far.z);
	if (t.nearest > t.farthest)
		return (false);
	if (t.farthest < 0)
		return (false);
	return (true);
}
