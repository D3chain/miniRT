/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:52:39 by echatela          #+#    #+#             */
/*   Updated: 2026/01/15 14:16:30 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOAD_H
# define LOAD_H

# include "minirt.h"

int		load_scene(struct s_app *app, const char *file);

int		scan_R(struct s_app *app, const char *line, int *_);
int		scan_C(struct s_app *app, const char *line, int *_);
int		scan_A(struct s_app *app, const char *line, int *_);
int		scan_L(struct s_app *app, const char *line, int *_);

int		scan_pl(struct s_app *app, const char *line, int *i_elem);
int		scan_sp(struct s_app *app, const char *line, int *i_elem);
int		scan_cy(struct s_app *app, const char *line, int *i_elem);
int		scan_co(struct s_app *app, const char *line, int *i_elem);

void	complete_RCAL(struct s_app *app);
void	complete_R(struct s_app *app, struct s_screen *screen);
void	complete_A(struct s_app *app, struct s_ambient *ambient);
void	complete_C(struct s_app *app, struct s_camera *camera, bool setup_pan_speed);
void	complete_L(struct s_app *app, struct s_light *light);

void	complete_pl(struct s_app *app, struct s_elem *elem);
void	complete_sp(struct s_app *app, struct s_elem *elem);
void	complete_cy(struct s_app *app, struct s_elem *elem);
void	complete_co(struct s_app *app, struct s_elem *elem);

#endif
