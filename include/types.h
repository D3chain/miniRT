/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:02:09 by echatela          #+#    #+#             */
/*   Updated: 2025/11/17 17:05:29 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdint.h>
# include "error.h"

// TYPE DEF

typedef enum e_status
{
	ERR_NONE	= 0,
	ERR_SYS		= 1,
	ERR_MLX		= 2,
	ERR_PARS	= 3
}	t_status;

typedef struct s_double3
{
	double	x;
	double	y;
	double	z;
}	t_double3;

union u_color
{
	uint32_t	value;
	struct {
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
		uint8_t	t;
	} s_rgb;
};

typedef union u_color	t_color;

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