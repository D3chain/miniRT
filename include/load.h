/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:52:39 by echatela          #+#    #+#             */
/*   Updated: 2026/01/20 20:31:52 by cgajean          ###   ########.fr       */
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

typedef int		(*t_scan_fn[N_SCENE_ITEMS])(struct s_app *, const char *, int);
typedef void	(*t_setup_fn[N_SCENE_ELEMS])(struct s_app *, struct s_elem *);

int		load_scene(struct s_app *app);

int		scan_r(struct s_app *app, const char *line, int _);
int		scan_c(struct s_app *app, const char *line, int _);
int		scan_a(struct s_app *app, const char *line, int _);
int		scan_l(struct s_app *app, const char *line, int _);

int		scan_pl(struct s_app *app, const char *line, int i_elem);
int		scan_sp(struct s_app *app, const char *line, int i_elem);
int		scan_cy(struct s_app *app, const char *line, int i_elem);
int		scan_co(struct s_app *app, const char *line, int i_elem);

void	scan_material(struct s_app *app, const char *line, t_material *mat);

void	setup_rcal(struct s_app *app);
void	setup_r(struct s_app *app, struct s_screen *screen);
void	setup_a(struct s_app *app, struct s_ambient *ambient);
void	setup_c(struct s_app *app, struct s_camera *camera, bool setup_pan_speed);
void	setup_l(struct s_app *app, struct s_light *light);

void	setup_pl(struct s_app *app, struct s_elem *elem);
void	setup_sp(struct s_app *app, struct s_elem *elem);
void	setup_cy(struct s_app *app, struct s_elem *elem);
void	setup_co(struct s_app *app, struct s_elem *elem);

#endif
