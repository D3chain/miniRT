/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:57:28 by echatela          #+#    #+#             */
/*   Updated: 2025/11/18 14:47:25 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_H
# define RUN_H

# include "minirt.h"

int run_scene(struct s_app *app);


// EVENTS
int	event_keyboard_press(int key, struct s_app *app);

// HIT
struct s_hit_info	compute_ray_collision(struct s_ray *ray, struct s_elem *elems, int n);
struct s_hit_info	(*ray_func(int type))(const struct s_ray*, const void*);
struct s_hit_info	ray_sphere(const struct s_ray *ray, const void *elem);
// DRAW
void    draw_pixel_to_img(struct s_img *img, int x, int y, int color);

#endif