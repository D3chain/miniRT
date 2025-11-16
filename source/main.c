/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:41:15 by echatela          #+#    #+#             */
/*   Updated: 2025/11/16 19:01:42 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	char			*title;
	void			*mlx;
	void			*win;
	struct s_img	img;
};

int	event_keyboard_press(int key, struct s_mlx *mlx)
{
	if (key == XK_Escape)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		mlx_destroy_display(mlx->mlx);
		exit(0);
	}
}


int	main(int argc, char *argv[])
{
	struct s_data	data;
	struct s_mlx	mlx;
	
	mlx.mlx = mlx_init();

	mlx.win = mlx_new_window(mlx.mlx, 800, 600, "Draw");

	mlx_hook(mlx.win, KeyPress, KeyPressMask, event_keyboard_press, &mlx);

	mlx_loop(mlx.mlx);
	
	return (0);
}
