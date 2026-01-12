/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 12:07:18 by echatela          #+#    #+#             */
/*   Updated: 2026/01/12 14:14:30 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "minirt.h"

typedef struct s_bvh_base t_bvh_base;


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

typedef struct s_antialiasing
{
	bool			enabled;
	int				oversampling;
	int				grid_size;

	t_color_linear	sample_color;

	t_double2		xy_offset;
	
} t_antialiasing;

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


/*	material	*/

typedef struct s_ray		t_ray;
typedef struct s_hit_info	t_hit_info;


struct s_ray
{
	t_double3	origin;
	t_double3	dir;
};

typedef struct s_material
{
	t_color			color;
	t_color_linear	color_linear;

	
	double	kd;				/*	diffuse color (albedo), THE object's color	*/
	double	ka;				/*	ambiant color								*/
	double	ks;				/*	specular color								*/
	
	double	shininess;		/*	nettete du reflet (10-200)					*/
	double	ks_intensity;	/*	intensite du reflet (0-1)					*/
	double	ior;			/*	indice de refraction						*/

	double	kr;
	double	kt;
} t_material;

struct s_hit_info
{
	bool		did_hit;
	double		dst;
	t_double3	hit_point;
	t_double3	normal;
	t_material	material;
};

typedef struct s_phong_effect
{
	t_ray		primary_ray;
	t_ray		shadow_ray;
	t_hit_info	hit_info;
	t_hit_info	shadow_hit;
	
	t_double3	N;	
	t_double3	P;	/*	point d'impact							*/
	t_double3	V;	/*	direction vers la camera				*/
	t_double3	L;	/*	direction vers la lumiere				*/
	t_double3	R;	/*	direction des reflexions (speculaire)	*/

	double		NdotL;
	double		RdotV;
	
	t_color	i_a;	/*	intensite ambient calculee		*/
	t_color	i_d;	/*	intensite diffuse calculee		*/
	t_color	i_s;	/*	intensite speculaire calculee	*/

	t_color_linear	ambient_light_color_linear;
	t_color_linear	light_color_linear;

	t_color_linear	diffuse_color_linear;
	t_color_linear	specular_color_linear;

	t_color_linear	final_color_linear;


	double	light_distance;
	
	double	fresnel_factor;
	double	specular_factor;

	bool	in_shadow;
} t_phong;

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
	t_double3	p1;
	t_double3	p2;
	t_double3	axis;
	double		radius;
	double		radius_sq;
	double		height;
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