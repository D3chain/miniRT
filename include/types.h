/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:02:09 by echatela          #+#    #+#             */
/*   Updated: 2025/11/16 19:54:38 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdint.h>
# include "error.h"

// TYPE DEF
struct s_xyz
{
	double	x;
	double	y;
	double	z;
};

union u_rgb
{
	uint32_t	color;
	struct {
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
		uint8_t	t;
	} s_rgb;
};

typedef struct s_xyz	t_point;
typedef struct s_xyz	t_dir;

typedef union u_rgb		t_rgb;

// ELEM
struct					s_elem;
struct					s_ambient_lightning;
struct					s_camera;
struct					s_light;
struct					s_sphere;
struct					s_plane;
struct					s_cylinder;
struct					s_scene;

#endif