/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:07:18 by echatela          #+#    #+#             */
/*   Updated: 2026/01/13 15:13:31 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

struct s_app;
struct s_scene;

# define 	FOCAL_LENGTH	1.0
// # define VIEW_HEIGHT	2.0
# define	N_SCENE_ITEMS	7
# define	N_SCENE_ELEMS	(N_SCENE_ITEMS - 3)


/*	refraction coefficients	*/
# define IOR_AIR    		1.0
# define IOR_WATER  		1.33
# define IOR_GLASS  		1.5
# define IOR_DIAMOND 		2.42
# define IOR_ENVIRONMENT	IOR_AIR

enum {
	PLANE		= 0,
	SPHERE		= 1,
	CYLINDER	= 2,
	CONE		= 3
};

/*	scene	*/

struct s_render
{
	int		resolution;	
	int		n_tiles;
	int		tile_side;
	int		tile_area;
};

struct s_camera
{
	t_double3	focal_center;
	t_double3	dir;
	double		fov;
	double		fov_rad;
	double		focal_length;
	double		viewport_width;
	double		viewport_height;
	t_double3	viewport_u;
	t_double3	viewport_u_px;
	t_double3	viewport_v;
	t_double3	viewport_v_px;
	t_double3	viewport_upper_left;
	t_double3	pixel00_loc;
};

struct s_ambient
{
	double			ratio;
	t_color			color;
	t_color_linear	color_linear;
};

struct s_light
{
	t_double3		coord;
	double			ratio;
	t_color			color;
	t_color_linear	color_linear;
	
};

struct s_antialiasing
{
	bool			enabled;
	int				oversampling;
	int				grid_size;

	t_color_linear	sample_color;

	t_double2		xy_offset;
	
};

struct s_scene
{
	struct s_camera			camera;

	struct s_ambient		ambient;

	struct s_light			*light;
	int						n_light;

	struct s_elem			*elems;
	int						n_elem;

	struct s_elem			*elems_inf;
	int						n_elem_inf;
	
	double					environment_ior;

	t_antialiasing			antialiasing;

	t_bvh_base				*bvh_root;
};


/* shapes */

struct s_sphere
{
	t_double3	coord;
	double		radius;
	double		radius_sq;
	t_material	material;
};

struct s_plane
{
	t_double3	coord;
	t_double3	normal;
	t_material	material;

};

struct s_cylinder
{
	t_double3	coord;
	t_double3	p1;
	t_double3	p2;
	t_double3	axis;
	double		radius;
	double		radius_sq;
	double		height;
	t_material	material;
};

struct s_cone
{
	t_double3	coord;
	t_double3	apex;
	t_double3	base;
	t_double3	axis;
	double		radius;
	double		radius_sq;
	double		height;
	double		theta;
	double		cos2_theta;
	t_material	material;
};
struct s_any
{
	t_double3	coord;
};

struct s_elem
{
	int		type;
	union {
		struct s_any		any;
		struct s_sphere 	sphere;
		struct s_plane		plane;
		struct s_cylinder	cylinder;
		struct s_cone		cone;
	}	u;
};

#endif
