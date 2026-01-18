/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel_to_img.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:43:53 by echatela          #+#    #+#             */
/*   Updated: 2026/01/18 01:08:59 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void draw_pixel_32bpp(struct s_img *img, t_int2 pos, int color)
{
	uint32_t offset = pos.y * (img->size_line >> 2) + pos.x;
	((uint32_t *)img->addr)[offset] = color;
}

static void draw_pixel_generic(struct s_img *img, t_int2 pos, int color)
{
	uint32_t pixel = (pos.y * img->size_line) + (pos.x * (img->bpp >> 3));
	*(uint32_t *)(img->addr + pixel) = color;
}

void init_draw_function(struct s_img *img)
{
	if (img->bpp == 32)
		img->draw_fn = draw_pixel_32bpp;
	else
		img->draw_fn = draw_pixel_generic;
}

void draw_pixel_to_img(struct s_img *img, t_int2 resolution, t_int2 pos, int color)
{
	if ((uint32_t)pos.x >= (uint32_t)resolution.x || 
		(uint32_t)pos.y >= (uint32_t)resolution.y)
		return;
	img->draw_fn(img, pos, color);
}
