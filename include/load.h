/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:52:39 by echatela          #+#    #+#             */
/*   Updated: 2026/01/21 17:14:43 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOAD_H
# define LOAD_H

# include "minirt_typedef.h"

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

#endif
