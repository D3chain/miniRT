/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:16:40 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/13 15:19:15 by cgajean          ###   ########.fr       */
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
	double	b;
	double	g;
	double	r;
	double	t;
};

struct s_material
{
	t_color			color;
	t_color_linear	color_linear;
	
	double	kd;
	double	ka;
	double	ks;
	
	double	shininess;
	double	ks_intensity;
	double	ior;

	double	kr;
	double	kt;
};

#endif
