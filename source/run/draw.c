/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:43:53 by echatela          #+#    #+#             */
/*   Updated: 2025/11/18 11:05:24 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void    draw_pixel_to_img(struct s_img *img, int x, int y, int color)
{
	unsigned int	pixel;

    if (x < 0 || x > WIN_WIDTH || y < 0 || y > WIN_HEIGHT)
        return ;
    pixel = (y * img->size_line) + (x * img->bpp / 8);
    img->addr[pixel + 0] = (color) & 0xff;
    img->addr[pixel + 1] = (color >> 8) & 0xff;
    img->addr[pixel + 2] = (color >> 16) & 0xff;
    img->addr[pixel + 3] = (color >> 24) & 0xff;
}
