/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 19:53:02 by echatela          #+#    #+#             */
/*   Updated: 2025/11/17 11:55:54 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

# include "minirt.h"

struct s_img
{
	
};

struct s_app
{
	void			*mlx;
	void			*win;
	struct s_img	img;

	

	struct s_scene	scene;

	t_status		status;
};

#endif