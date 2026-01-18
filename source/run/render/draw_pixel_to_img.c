/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel_to_img.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:43:53 by echatela          #+#    #+#             */
/*   Updated: 2026/01/18 20:52:49 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

__attribute__((hot))
void draw_pixel_to_img(struct s_img *img, t_int2 resolution, t_int2 pos, int color)
{
	uint32_t	pixel;
	
	if ((uint32_t)pos.x >= (uint32_t)resolution.x || 
		(uint32_t)pos.y >= (uint32_t)resolution.y)
		return;
	pixel = (pos.y * img->size_line) + (pos.x * (img->bpp >> 3));
	*(uint32_t *)(img->addr + pixel) = color;
}
