/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 13:57:25 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/14 13:57:39 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cleanup_app(struct s_app *app)
{
	if (app->mlx.mlx)
	{
		if (app->mlx.win)
			mlx_destroy_window(app->mlx.mlx, app->mlx.win);
		if (app->mlx.img.img)
			mlx_destroy_image(app->mlx.mlx, app->mlx.img.img);
		mlx_destroy_display(app->mlx.mlx);
		free(app->mlx.mlx);
	}
	if (app->scene.elems)
		free(app->scene.elems);
}
