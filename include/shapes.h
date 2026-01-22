/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:19:47 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/22 13:53:07 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "minirt_typedef.h"
# include "types.h"
# include "material.h"

struct s_sphere
{
	t_material	material;
	t_real3		coord;
	t_real		radius;
	t_real		radius_sq;
};

struct s_plane
{
	t_material	material;
	t_real3		coord;
	t_real3		normal;
};

struct s_cylinder
{
	t_material	material;
	t_real3		coord;
	t_real3		p1;
	t_real3		p2;
	t_real3		axis;
	t_real		radius;
	t_real		radius_sq;
	t_real		height;
};

struct s_cone
{
	t_material	material;
	t_real3		coord;
	t_real3		apex;
	t_real3		base;
	t_real3		axis;
	t_real		radius;
	t_real		radius_sq;
	t_real		height;
	t_real		theta;
	t_real		cos2_theta;
};

struct s_any
{
	t_material	material;
	t_real3		coord;
};

struct s_shape
{
	int		type;
	union {
		t_any		any;
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
		t_cone		cone;
	}	u_;
};

#endif
