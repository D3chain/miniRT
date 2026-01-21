/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:07:18 by echatela          #+#    #+#             */
/*   Updated: 2026/01/21 17:20:59 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "minirt_typedef.h"
# include "types.h"
# include "sys/time.h"

# define FOCAL_LENGTH	FLT_1
# define N_SCENE_ITEMS	8
# define N_SETUP_ITEMS	4
# define N_SCENE_ELEMS	4

enum {
	R	= 0,
	C	= 1,
	A	= 2,
	L	= 3
};

enum {
	PLANE		= 0,
	SPHERE		= 1,
	CYLINDER	= 2,
	CONE		= 3
};

enum {
	MOVE_CAMERA_ANGLE,
	MOVE_CAMERA_POS
};

enum {
	MID_ZOOM,
	MID_TILT	
};

//	MOUSE
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
	int				button;

	t_mouse_pos		pos;

	struct timeval	last_action_time;
	bool			is_scrolling;

	t_real			pan_speed;
	t_real			base_pan_speed;

	bool			fast_move;
};

//	VIEWPORT
struct s_viewport
{
	t_real		width;
	t_real		height;
	t_real3		u;
	t_real3		u_px;
	t_real3		v;
	t_real3		v_px;
	t_real3		upper_left;

	t_real3		pixel00_loc;
};

//	CAMERA
struct s_camera
{
	t_real3		focal_center;
	t_real3		dir;

	t_real3		dir_up;
	t_real3		dir_right;

	t_real		focal_length;
	t_real		fov;
	t_real		fov_rad;

	t_real		fov_reference;
	t_real		pan_fov_ratio;

	t_viewport	wp;

	t_mouse		mouse;
};

//	LIGHTS
struct s_ambient
{
	t_real		ratio;
	t_color		color;
	t_color_lin	color_linear;
};

struct s_light
{
	t_real3		coord;
	t_real		ratio;
	t_color		color;
	t_color_lin	color_linear;
};

//	SCENE
struct s_scene
{
	t_camera	camera;

	t_ambient	ambient;

	t_light		*light;
	int			n_light;

	t_shape		*elems;
	int			n_elem;

	t_shape		*elems_inf;
	int			n_elem_inf;

	t_real		environment_ior;

	t_bvh_base	*bvh_root;
};

#endif
