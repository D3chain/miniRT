/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 19:53:02 by echatela          #+#    #+#             */
/*   Updated: 2026/01/22 13:58:09 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

# include "minirt_typedef.h"
# include "types.h"

typedef t_int2	t_resolution;

enum e_status
{
	ERR_NONE	= 0,
	ERR_SYS		= 1,
	ERR_MLX		= 2,
	ERR_PARS	= 3
};

struct s_screen
{
	t_resolution	resolution;
	t_real			img_ratio;
};

struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
};

struct s_mlx
{
	char		*title;
	void		*mlx;
	void		*win;

	t_screen	screen;	
	t_img		img;
};

struct s_app
{
	t_status	status;
	char		*file_name;

	t_mlx		mlx;
	t_scene		scene;
	t_render	render;
	t_thread	threads;
};

/*	app	*/
int		init_app(t_app *app);
void	cleanup_app(t_app *app);

#endif
