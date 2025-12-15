/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 19:53:02 by echatela          #+#    #+#             */
/*   Updated: 2025/12/15 15:48:06 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

# include "minirt.h"

struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
};

struct	s_mlx
{
	const char		*title;

	void			*mlx;

	void			*win;
	int				width;
	int				height;

	struct s_img	img;
};

struct s_app
{
	struct s_mlx	mlx;

	struct s_scene	scene;

	t_status		status;
};

#endif