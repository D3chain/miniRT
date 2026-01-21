/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_typedef.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:21:12 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/21 17:12:38 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_TYPEDEF_H
# define MINIRT_TYPEDEF_H

/*	app.h	*/
typedef struct s_app			t_app;
typedef struct s_mlx			t_mlx;
typedef struct s_img			t_img;
typedef struct s_screen			t_screen;
typedef enum e_status			t_status;

/*	bvh.h	*/
typedef struct s_bounding_box	t_boundbox;
typedef struct s_bvh_base		t_bvh_base;
typedef struct s_bvh_elem_box	t_bvh_elem_box;
typedef struct s_bvh_node		t_bvh_node;

/*	mathematics.h*/
typedef struct s_sol2			t_sol2;

/*	phong_effect.h*/
typedef struct s_phong_effect	t_phong;

/*	ray.h	*/
typedef struct s_ray			t_ray;
typedef struct s_hit_info		t_hit_info;

/*	render.h	*/
typedef struct s_render			t_render;
typedef struct s_antialiasing	t_antialiasing;
typedef struct s_thread			t_thread;

/*	scene.h	*/
typedef struct s_scene			t_scene;

typedef struct s_camera			t_camera;
typedef struct s_viewport		t_viewport;
typedef struct s_light			t_light;
typedef struct s_ambient		t_ambient;

typedef struct s_mouse			t_mouse;
typedef struct s_mouse_position	t_mouse_pos;

/*	shapes.h	*/
typedef struct s_plane			t_plane;
typedef struct s_sphere			t_sphere;
typedef struct s_cylinder		t_cylinder;
typedef struct s_cone			t_cone;
typedef struct s_any			t_any;
typedef struct s_shape			t_shape;

/*	load.h	*/
typedef void					(*t_setup_fn[])(t_app *, t_shape *);

/*	types.h	*/
typedef struct s_int2			t_int2;
typedef struct s_int3			t_int3;

typedef struct s_real2			t_real2;
typedef struct s_real3			t_real3;

/*	material.h	*/
typedef union u_color			t_color;
typedef struct s_color_linear	t_color_lin;
typedef struct s_material		t_material;

#endif
