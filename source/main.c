/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:41:15 by echatela          #+#    #+#             */
/*   Updated: 2025/11/14 12:27:06 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	init_scene(struct s_scene *scene, int argc, char *argv[])
{
	if (argc != 2 || !is_file_format_correct(argv[1]))
		return (1);
	ft_bzero(scene, sizeof(*scene));
}

int	main(int argc, char *argv[])
{
	struct s_scene	scene;

	if (init_scene(&scene, argc, argv) != 0)
		return (1);
	if (process_scene(&scene) != 0)
		return (1);
	clear_scene(&scene);
	return (0);
}