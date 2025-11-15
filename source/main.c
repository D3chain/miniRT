/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:41:15 by echatela          #+#    #+#             */
/*   Updated: 2025/11/15 15:55:20 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	quit(struct s_data *data)
{
	clear_data(&data);
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
