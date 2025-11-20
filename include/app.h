/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 19:53:02 by echatela          #+#    #+#             */
/*   Updated: 2025/11/20 17:12:55 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

# include "minirt.h"

# ifndef WIN_WIDTH
#  define WIN_WIDTH 800
# endif

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 600
# endif

# define IMG_RATIO	(double)(WIN_WIDTH / WIN_HEIGHT)

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