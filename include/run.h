/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:57:28 by echatela          #+#    #+#             */
/*   Updated: 2026/01/13 15:48:38 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_H
# define RUN_H

# include "minirt.h"


int run_scene(struct s_app *app);
int	render(struct s_app *app);

// RENDER
void 			*render_routine(void *p);

// void			render(struct s_app *app);
t_color_linear	trace(struct s_scene *scene, const t_ray *ray);

// EVENTS
int				event_keyboard_press(int key, struct s_app *app);

// DRAW
void  			draw_pixel_to_img(struct s_img *img, int x, int y, int color);

#endif
