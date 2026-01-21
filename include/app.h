/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 19:53:02 by echatela          #+#    #+#             */
/*   Updated: 2026/01/21 12:44:27 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

typedef t_int2	t_resolution;

struct s_screen
{
	t_resolution	resolution;
	t_real			img_ratio;
};

struct s_img
{
	void			*img;
	char			*addr;
	int				bpp;
	int				size_line;
	int				endian;
};

struct s_mlx
{
	const char		*title;

	void			*mlx;

	void			*win;
	
	t_screen	screen;	

	t_img	img;
};

struct s_thread
{
	pthread_t		*th_tab;
	_Atomic	int 	th_idx;
	int				cpu_cores;
};

struct s_render
{
	int				resolution;	
	int				n_tiles;
	int				tile_side;
	t_real			inv_tile_side;
	int				tile_area;

	t_antialiasing	antialiasing;
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

/*	PROTOTYPES	*/

int		init_app(t_app *app);
void	cleanup_app(t_app *app);

#endif
