/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tone_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: focol <focol@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 23:41:45 by fox               #+#    #+#             */
/*   Updated: 2025/12/16 23:51:13 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color_linear	tone_map_clamp(t_color_linear col)
{
	if (col.r > 1)
		col.r = 1;
	if (col.g > 1)
		col.g = 1;
	if (col.b > 1)
		col.b = 1;	
	return (col);
}

t_color_linear tone_map_reinhard(t_color_linear col)
{
	col.r = col.r / (1.5 + col.r);
    col.g = col.g / (1.5 + col.g);
   	col.b = col.b / (1.5 + col.b);
    return (col);
}

t_color_linear tone_map_aces(t_color_linear col)
{
	static const t_real	a = 2.51;
	static const t_real	b = 0.03;
	static const t_real	c = 2.43;
	static const t_real	d = 0.59;
	static const t_real	e = 0.14;

	col.r = (col.r * (a * col.r + b)) / (col.r * (c * col.r + d) + e);
	if (col.r - 1.0 > EPSILON)
		col.r = 1;
	col.g = (col.g * (a * col.g + b)) / (col.g * (c * col.g + d) + e);
	if (col.g - 1.0 > EPSILON)
		col.g = 1;	
	col.b = (col.b * (a * col.b + b)) / (col.b * (c * col.b + d) + e);
	if (col.b - 1.0 > EPSILON)
		col.b = 1;	
	return (col);
}

t_color_linear tone_map_luminance(t_color_linear col)
{
	t_real L = 0.2126 * col.r + 0.7152 * col.g + 0.0722 * col.b;	// Calcul de la luminance perceptuelle

	if (L <= 0.0001)
		return (col);

	t_real L_compressed = L / (1.0 + L);	// Compression de la luminance
	t_real scale = L_compressed / L;		// Application du ratio à toutes les composantes

	col.r *= scale;
	col.g *= scale;
	col.b *= scale;
    return (col);
}
