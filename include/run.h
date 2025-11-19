/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:57:28 by echatela          #+#    #+#             */
/*   Updated: 2025/11/19 15:31:05 by cgajean          ###   ########.fr       */
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
struct s_hit_info	ray_cylinder(const struct s_ray *ray, const void *elem);

double	plane_dst(const struct s_ray *ray, const t_double3 normal, const t_double3 point);

// DRAW
void    draw_pixel_to_img(struct s_img *img, int x, int y, int color);

// UTIL
double				closest_hit_dst_dbl(const double a, const double b);
double				closest_hit_dst_sol2(t_sol2 sol);



#endif