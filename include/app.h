/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 19:53:02 by echatela          #+#    #+#             */
/*   Updated: 2026/01/15 16:58:03 by cgajean          ###   ########.fr       */
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

struct s_mouse
{
	int				button;
	t_int2			pos_cur;
	t_int2			pos_prv;
	t_int2			dir;
};

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
	int				tile_area;

	struct s_mouse	mouse;
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
int		init_scene(struct s_app *app, const char *filename);
void	cleanup_app(struct s_app *app);

#endif
