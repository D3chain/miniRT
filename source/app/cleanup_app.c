/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_app.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 13:57:25 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/21 11:50:18 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	clean_scene(t_scene *scene)
{
	if (scene->light)
		free(scene->light);
	if (scene->elems)
		free(scene->elems);
	if (scene->elems_inf)
		free(scene->elems_inf);
}

static void	clean_mlx(t_mlx *mlx)
{
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->img.img)
		mlx_destroy_image(mlx->mlx, mlx->img.img);
	if (mlx->mlx)
	{
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
}

static void	clean_threading(t_thread *t)
{
	if (t->th_tab)
		free(t->th_tab);
}

void	cleanup_app(t_app *app)
{
	clean_scene(&app->scene);
	bvh_destroy(app->scene.bvh_root);
	clean_threading(&app->threads);
	clean_mlx(&app->mlx);
}
