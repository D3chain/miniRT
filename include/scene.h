/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:07:18 by echatela          #+#    #+#             */
/*   Updated: 2025/11/18 11:16:39 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "minirt.h"
# include "types.h"

enum {
	SPHERE		= 1,
	PLANE		= 2,
	CYLINDER	= 4
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
	int						nb_elem;
};

/* shapes */

struct s_sphere
{
	t_double3	coord;
	double		diametre;
	t_color		color;
};

struct s_plane
{
	t_double3	coord;
	t_double3	direction;
};

struct s_cylinder
{
	t_double3	coord;
	t_double3	direction;
	double		diametre;
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
};

#endif