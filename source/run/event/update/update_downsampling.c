/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_downsampling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:24:42 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/19 16:24:44 by cgajean          ###   ########.fr       */
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
