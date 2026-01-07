/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit_cone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 10:46:36 by echatela          #+#    #+#             */
/*   Updated: 2026/01/07 11:00:07 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

struct s_hit_info	ray_hit_cone(const struct s_ray *ray, const void *elem)
{
	struct s_hit_info	closest_hit;
	const struct s_cone	cone = ((struct s_elem *)elem)->u.cone;
}