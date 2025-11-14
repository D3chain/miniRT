/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:07:18 by echatela          #+#    #+#             */
/*   Updated: 2025/11/14 17:22:06 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "types.h"

enum {
	SPHERE		= 1,
	PLANE		= 2,
	CYLINDER	= 4
};

struct s_scene
{
	struct s_camera			camera;

	struct s_ambient_light	ambient_light;

	struct s_light			light;

	struct s_elem			*elems;
	int						nb_elem;
};

struct s_elem
{
	int		type;
};

struct s_ambient_light
{
	double	ratio;
	t_rgb	color;
};

struct s_camera
{
	t_point	coord;
	t_dir	direction;
	int		fov;
};

struct s_light
{
	t_point	coord;
	double	ratio;
};

struct s_sphere
{
	int		type;
	t_point	coord;
	double	diametre;
	t_rgb	color;
};

struct s_plane
{
	int		type;
	t_point	coord;
	t_dir	direction;
};

struct s_cylinder
{
	int		type;
	t_point	coord;
	t_dir	direction;
	double	diametre;
	double	height;
	t_rgb	color;
};



#endif