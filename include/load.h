/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:52:39 by echatela          #+#    #+#             */
/*   Updated: 2026/01/17 20:59:15 by fox              ###   ########.fr       */
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

void	setup_RCAL(struct s_app *app);
void	setup_R(struct s_app *app, struct s_screen *screen);
void	setup_A(struct s_app *app, struct s_ambient *ambient);
void	setup_C(struct s_app *app, struct s_camera *camera, bool setup_pan_speed);
void	setup_L(struct s_app *app, struct s_light *light);

void	setup_pl(struct s_app *app, struct s_elem *elem);
void	setup_sp(struct s_app *app, struct s_elem *elem);
void	setup_cy(struct s_app *app, struct s_elem *elem);
void	setup_co(struct s_app *app, struct s_elem *elem);

#endif
