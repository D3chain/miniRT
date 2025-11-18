/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:08:41 by echatela          #+#    #+#             */
/*   Updated: 2025/11/18 11:10:09 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	hit_sphere(struct s_ray *ray, struct s_sphere *sphere)
{
	double	a;
	double	b;
	double	c;
	double	dis;
	t_double3	off_ray_origin;

	off_ray_origin = minus3(ray->origin, sphere->coord);
	a = dot(ray->dir, ray->dir); // toujours 1;
	b = 2 * dot(off_ray_origin, ray->dir);
	c = dot(off_ray_origin, off_ray_origin) - pow(sphere->diametre / 2, 2.0);
	dis = pow(b, 2.0) - 4 * 1 * c;

	if (dis >= 0)
	{
		float	dst = (-b - sqrt(dis)) / (2 * a);
		if (dst >= 0)
			return (1);
	}
	return (0);
}

bool	hit(struct s_ray *ray, struct s_elem *elems, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (elems[i].type == SPHERE && hit_sphere(ray, &elems[i].u.sphere))
			return (1);
		i++;
	}
	return (0);
}
