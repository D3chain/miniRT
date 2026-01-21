/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:52:39 by echatela          #+#    #+#             */
/*   Updated: 2026/01/21 13:00:25 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOAD_H
# define LOAD_H

# include "minirt.h"

# define MAT_FACTORS		{"k_amb", "k_dif", "k_spc", "shine", "ior__"}
# define N_MAT_FACTORS		5
# define LEN_FACTOR_NAME	5
# define MIN_NORM_VALUE		FLT_0_1
# define MIN_SHI_VALUE		FLT_10

enum {
	K_AMB,
	K_DIF,
	K_SPC,
	shine,
	IOR__	
};

int		load_scene(t_app *app);
int		scan_file_line(t_app *app, const char *line);


int		scan_r(t_app *app, const char *line, int _);
int		scan_c(t_app *app, const char *line, int _);
int		scan_a(t_app *app, const char *line, int _);
int		scan_l(t_app *app, const char *line, int _);

int		scan_pl(t_app *app, const char *line, int i_elem);
int		scan_sp(t_app *app, const char *line, int i_elem);
int		scan_cy(t_app *app, const char *line, int i_elem);
int		scan_co(t_app *app, const char *line, int i_elem);

void	scan_material(t_app *app, const char *line, t_material *mat);

void	setup_rcal(t_app *app);
void	setup_r(t_app *app, t_screen *screen);
void	setup_a(t_app *app, t_ambient *ambient);
void	setup_c(t_app *app, t_camera *camera, bool setup_pan_speed);
void	setup_l(t_app *app, t_light *light);

void	setup_pl(t_app *app, t_shape *elem);
void	setup_sp(t_app *app, t_shape *elem);
void	setup_cy(t_app *app, t_shape *elem);
void	setup_co(t_app *app, t_shape *elem);

#endif
