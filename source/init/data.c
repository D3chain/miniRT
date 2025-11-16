/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:05:05 by echatela          #+#    #+#             */
/*   Updated: 2025/11/16 19:55:57 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_arg(struct s_data *data, int argc, char *argv[])
{
	if (argc != 2 || ft_strrcmp(argv[1], ".rt"))
	{
		data->status = ERR_PARS;
		ft_printf("Usage: %s <filename.rt>\n", argv[0]);
		return (1);
	}
	return (0);
}

static int	init_mlx(struct s_data *data)
{
	data.
}

int	init_data(struct s_data *data, int argc, char *argv[])
{
	ft_bzero(data, sizeof(*data));
	if (check_arg(data, argc, argv))
		return (data->status);
	if (init_mlx(data))
		return (data->status);
	return (ERR_NONE);
}
