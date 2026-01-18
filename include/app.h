/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 19:53:02 by echatela          #+#    #+#             */
/*   Updated: 2026/01/18 20:53:29 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

typedef t_int2	t_resolution;

struct s_app;
struct s_scene;

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

struct	s_mlx
{
	const char		*title;

	void			*mlx;

	void			*win;
	
	struct s_screen	screen;	

	struct s_img	img;
};

struct	s_thread
{
	pthread_t		*th_tab;
	
	pthread_mutex_t	th_idx_mtx;
	int				th_idx;

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
	struct s_mlx	mlx;

	struct s_scene	scene;

	struct s_render	render;

	struct s_thread	threads;
	
	t_status		status;
};

/*	PROTOTYPES	*/

int		init_app(struct s_app *app, int argc, char *argv[]);

void	cleanup_app(struct s_app *app);

#endif
