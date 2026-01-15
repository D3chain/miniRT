/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel_to_img.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:43:53 by echatela          #+#    #+#             */
/*   Updated: 2026/01/15 11:32:01 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void    draw_pixel_to_img(struct s_img *img, t_int2 resolution, t_int2 pos, int color)
{
	unsigned int	pixel;

    if (pos.x < 0 || pos.x > resolution.x || pos.y < 0 || pos.y > resolution.y)
        return ;
    pixel = (pos.y * img->size_line) + (pos.x * img->bpp / 8);
    img->addr[pixel + 0] = (color) & 0xff;
    img->addr[pixel + 1] = (color >> 8) & 0xff;
    img->addr[pixel + 2] = (color >> 16) & 0xff;
    img->addr[pixel + 3] = (color >> 24) & 0xff;
}
