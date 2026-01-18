/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_downsampling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 19:07:23 by fox               #+#    #+#             */
/*   Updated: 2026/01/18 19:58:28 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

inline void	increase_downsampling(t_antialiasing *a)
{
	if (a->downsample_activation == false)
	{
		a->downsample_activation = true;
		printf("\nDownsampling is enabled\n");
	}
	if (a->downsample_rate != MAX_DOWNSAMPLING_RATE)
	{
		a->downsample_rate *= 2;
		printf("Downsampling=%dx\n", a->downsample_rate);
	}
}

inline void	decrease_downsampling(t_antialiasing *a)
{
	if (a->downsample_rate <= MIN_DOWNSAMPLING_RATE)
	{
		a->downsample_activation = false;
		printf("\nDownsampling is disabled.\n");
	}
	else
	{
		a->downsample_rate /= 2;
		printf("Downsampling=%dx\n", a->downsample_rate);
	}
}

void	start_downsampling(t_antialiasing *a)
{
	if (a->downsample_activation)
		a->tfn = render_tile_downsampled;
}

void	stop_downsampling(t_antialiasing *a)
{
	a->tfn = render_tile;
}

void	toggle_downsampling(t_antialiasing *a)
{
	a->downsample_activation = !a->downsample_activation;
	if (!a->downsample_activation)
		stop_downsampling(a);
	printf("Downsampling:%d\n", a->downsample_activation);
}
