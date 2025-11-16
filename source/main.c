/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:41:15 by echatela          #+#    #+#             */
/*   Updated: 2025/11/16 17:37:35 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* fake functions for compilation */
int process_scene(struct s_data *data)
{
	(void) data;
	return (1);
}

void	clear_data(struct s_data *data)
{
	(void) data;
}

/**** */

static int	quit(struct s_data *data)
{
	clear_data(data);
	return (data->status);
}

int	main(int argc, char *argv[])
{
	struct s_data	data;

	if (init_data(&data, argc, argv))
		return (quit(&data));
	if (process_scene(&data))
		return (quit(&data));
	return (quit(&data));
}
