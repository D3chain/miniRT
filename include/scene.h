/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:07:18 by echatela          #+#    #+#             */
/*   Updated: 2025/11/18 16:19:32 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "minirt.h"
# include "types.h"

enum {
	PLANE		= 0,
	SPHERE		= 1,
	CYLINDER	= 2
};

struct s_camera
{
	t_double3	coord;
	t_double3	dir;
	int			fov;
};

struct s_ambient_light
{
	t_double3	ratio;
	t_color		color;
};

struct s_light
{
	t_double3	coord;
	double		ratio;
};

struct s_scene
{
	struct s_camera			camera;

	struct s_ambient_light	ambient_light;

	struct s_light			light;

	struct s_elem			*elems;
	int						n_elem;
};

/* shapes */

struct s_sphere
{
	t_double3	coord;
	double		radius;
	t_color		color;
};

struct s_plane
{
	t_double3	coord;
	t_double3	normal;
	t_color		color;
};

struct s_cylinder
{
	t_double3	coord;
	t_double3	normal;
	double		radius;
	double		height;
	t_color		color;
};

struct s_elem
{
	int		type;
	union {
		struct s_sphere 	sphere;
		struct s_plane		plane;
		struct s_cylinder	cylinder;
	}	u;
};

struct s_ray
{
	t_double3	origin;
	t_double3	dir;
};

struct s_hit_info
{
	bool		did_hit;
	double		dst;
	t_double3	hit_point;
	t_double3	normal;
	t_color		color_material;
};

#endif
