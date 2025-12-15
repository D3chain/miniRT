/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:07:18 by echatela          #+#    #+#             */
/*   Updated: 2025/12/15 11:19:54 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "minirt.h"

# define 	FOCAL_LENGTH	1.0
// # define VIEW_HEIGHT	2.0
# define	N_SCENE_ITEMS	6
# define	N_SCENE_ELEMS	(N_SCENE_ITEMS - 3)

enum {
	PLANE		= 0,
	SPHERE		= 1,
	CYLINDER	= 2
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
	double		ratio;
	t_color		color;
};

struct s_light
{
	t_double3	coord;
	double		ratio;
	t_color		color;
	// t_color		i_i;	/*	light intensity	*/
};

struct s_scene
{
	struct s_camera			camera;

	struct s_ambient		ambient;

	struct s_light			light;

	struct s_elem			*elems;
	int						n_elem;
};

/* shapes */

struct s_sphere
{
	t_double3	coord;
	double		radius;
	double		radius_sq;
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
	t_double3	axis;
	double		radius;
	double		radius_sq;
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

struct s_material
{
	t_color	color;	/*	material color			*/
	
	t_color	ks;		/*	specular color			*/
	t_color	kd;		/*	diffuse color (albedo)	*/
	t_color	ka;		/*	ambiant color			*/
	
	t_color	i_s;	/*	specular result			*/
	t_color	i_d;	/*	diffuse result			*/

	double	shininess;
	double	i_or;	/*	refraction				*/
};


#endif

// // VECTEURS (directions, positions)
// t_vector normal;           // N
// t_vector view_dir;         // V
// t_vector light_dir;        // L
// t_vector reflection_dir;   // R
// t_vector incident_dir;     // I

// // COULEURS (RGB)
// t_color light_color;       // Ii (couleur de lumière)
// t_color specular_color;    // ks (couleur spéculaire matériau)
// t_color diffuse_color;     // kd (couleur diffuse matériau)
// t_color result_specular;   // Is
// t_color result_diffuse;    // Id

// // SCALAIRES (nombres)
// double fresnel_coef;       // R de Schlick
// double shininess;          // n (exposant)
// double cos_theta;          // N·V ou R·V
// double light_ratio;        // intensité lumière
// double n1, n2;             // indices réfraction