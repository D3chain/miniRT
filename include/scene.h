/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:07:18 by echatela          #+#    #+#             */
/*   Updated: 2026/01/17 12:49:36 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "minirt.h"

struct s_app;
struct s_scene;

# define 	FOCAL_LENGTH	FLT_1
// # define VIEW_HEIGHT	2.0
# define	N_SCENE_ITEMS	8
# define	N_SETUP_ITEMS	4
# define	N_SCENE_ELEMS	(N_SCENE_ITEMS - N_SETUP_ITEMS)



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

# define	N_MOVE_OPTIONS	2

enum {
	MOVE_CAMERA_ANGLE,
	MOVE_CAMERA_POS
};

enum {
	MID_ZOOM,
	MID_TILT	
};


/*	scene	*/

struct s_mouse_motion
{
	t_real	pan_speed;
	t_real	base_pan_speed;

	bool	fast_move;
};


struct s_mouse_position
{
	t_int2			cur;
	t_int2			prv;
	t_int2			dir;
};

struct s_mouse
{
	int						button;

	struct s_mouse_position	pos;
	
	struct s_mouse_motion	zoom;
	struct s_mouse_motion	motion;

	struct timeval			last_action_time;
	bool					is_scrolling;
};

struct s_viewport
{
	t_real	width;
	t_real	height;
	t_real3	u;
	t_real3	u_px;
	t_real3	v;
	t_real3	v_px;
	t_real3	upper_left;
	
	t_real3	pixel00_loc;
};

struct s_camera
{
	t_real3				focal_center;
	t_real3				dir;

	t_real3				dir_up;
	t_real3				dir_right;
	
	t_real				focal_length;
	t_real				fov;
	t_real				fov_rad;
	
	t_real				fov_reference;
	t_real				pan_fov_ratio;
	
	struct s_viewport	wp;

	struct s_mouse		mouse;
};

struct s_ambient
{
	t_real			ratio;
	t_color			color;
	t_color_linear	color_linear;
};

struct s_light
{
	t_real3			coord;
	t_real			ratio;
	t_color			color;
	t_color_linear	color_linear;
	
};

struct s_antialiasing
{
	bool			enabled;
	int				oversampling;
	int				grid_size;
	
	t_color_linear	sample_color;

	t_real2			xy_offset;
	
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
	
	t_real					environment_ior;

	t_bvh_base				*bvh_root;
};


/* shapes */

struct s_sphere
{
	t_real3	coord;
	t_real		radius;
	t_real		radius_sq;
	t_material	material;
};

struct s_plane
{
	t_real3	coord;
	t_real3	normal;
	t_material	material;

};

struct s_cylinder
{
	t_real3	coord;
	t_real3	p1;
	t_real3	p2;
	t_real3	axis;
	t_real		radius;
	t_real		radius_sq;
	t_real		height;
	t_material	material;
};

struct s_cone
{
	t_real3	coord;
	t_real3	apex;
	t_real3	base;
	t_real3	axis;
	t_real		radius;
	t_real		radius_sq;
	t_real		height;
	t_real		theta;
	t_real		cos2_theta;
	t_material	material;
};
struct s_any
{
	t_real3	coord;
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
