/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:41:15 by echatela          #+#    #+#             */
/*   Updated: 2025/11/16 19:49:50 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* phony functions for compilation */
int process_scene(struct s_data *data)
{
	(void) data;
	return (1);
}

void	clear_data(struct s_data *data)
{
	(void) data;
}

void	mlx_create(void)
{
	void	*mlx = mlx_init();
	(void) mlx;
	mlx_destroy_display(mlx);
}

/**** */

static int	quit(struct s_data *data)
{
	print_error(data);
	cleanup_data(data);
	return (data->status);
}

int	main(int argc, char *argv[])
{
	struct s_data	data;

	if (init_data(&data, argc, argv))
		return (quit(&data));
	if (load_scene(&data, argv[1]))
		return (quit(&data));
	if (process_scene(&data))
		return (quit(&data));
	return (quit(&data));
}
