/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:02:09 by echatela          #+#    #+#             */
/*   Updated: 2026/01/09 15:52:09 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "minirt.h"

// TYPE DEF

typedef enum e_status
{
	ERR_NONE	= 0,
	ERR_SYS		= 1,
	ERR_MLX		= 2,
	ERR_PARS	= 3
}	t_status;

typedef struct s_double2
{
	double	x;
	double	y;
}	t_double2;

typedef struct s_double3
{
	double	x;
	double	y;
	double	z;
}	t_double3;

// ELEM
struct	s_elem;
struct	s_ambient_lightning;
struct	s_camera;
struct	s_light;
struct	s_sphere;
struct	s_plane;
struct	s_cylinder;
struct	s_scene;

#endif