/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:19:03 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/19 16:30:39 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# include <stdint.h>

/* Types de couleur */
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

struct s_color_linear {
	t_real	b;
	t_real	g;
	t_real	r;
};

struct s_material
{
	t_color			color;
	t_color_linear	color_linear;
	
	t_real	kd;
	t_real	ka;
	t_real	ks;
	
	t_real	shininess;
	t_real	ior;
};

#endif
