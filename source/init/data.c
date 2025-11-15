/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:05:05 by echatela          #+#    #+#             */
/*   Updated: 2025/11/14 18:59:24 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	check_arg(struct s_data *data, int argc, char *argv[])
{
	if (argc != 2 || ft_strrcmp(argv[1], ".rt"))
	{
		data->status = ERR_PARS;
		ft_printf("Usage: %s <filename.rt>\n", argv[0]);
		return (1);
	}
	return (0);
}

bool	init_data(struct s_data *data, int argc, char *argv[])
{
	ft_bzero(data, sizeof(*data));
	if (check_arg(data, argc, argv))
		return (1);
	if (init_scene(data, argv[1]))
		return (1);
	if (init_mlx(data))
		return (1);
	return (0);
}
