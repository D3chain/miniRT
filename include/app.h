/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 19:53:02 by echatela          #+#    #+#             */
/*   Updated: 2026/01/13 17:01:25 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

struct s_app;
struct s_scene;

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

struct	s_thread
{
	pthread_t		*th_tab;
	
	pthread_mutex_t	th_idx_mtx;
	int				th_idx;

	pthread_mutex_t	print_mtx;

	int				cpu_cores;
};

struct s_app
{
	struct s_mlx	mlx;

	struct s_scene	scene;

	struct s_render	render;

	struct s_thread	threads;
	
	t_status		status;
};

#endif
