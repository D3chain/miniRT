/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_typedef.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:01:20 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/13 23:26:38 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_TYPEDEF
# define MINIRT_TYPEDEF

# ifdef USE_DBL_NUMBER
	typedef double				t_real;
# else
	typedef float				t_real;
# endif

typedef enum e_status			t_status;

typedef struct s_int2			t_int2;
typedef struct s_int3			t_int3;
	
typedef struct s_real2			t_real2;
typedef struct s_real3			t_real3;

typedef struct s_bounding_box	t_boundbox;
typedef struct s_bvh_base		t_bvh_base;
typedef struct s_bvh_elem_box	t_bvh_elem_box;
typedef struct s_bvh_node		t_bvh_node;

typedef struct s_ray			t_ray;
typedef struct s_hit_info		t_hit_info;

typedef union u_color			t_color;
typedef struct s_color_linear	t_color_linear;
typedef struct s_material		t_material;

typedef struct s_sol2			t_sol2;

typedef struct s_phong_effect	t_phong;

typedef struct s_antialiasing	t_antialiasing;

#endif