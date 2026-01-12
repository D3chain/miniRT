/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:57:28 by echatela          #+#    #+#             */
/*   Updated: 2026/01/12 14:14:21 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_H
# define RUN_H

# include "minirt.h"

typedef struct s_bvh_elem_box	t_bvh_elem_box;

int run_scene(struct s_app *app);



// RENDER
void			render(struct s_app *app);
void			init_ray(struct s_app *app, struct s_ray *ray, double x, double y);
// t_color_linear	trace(struct s_scene *scene, const t_ray *ray);
t_color_linear	trace(struct s_scene *scene, const t_ray *ray);




// EVENTS
int	event_keyboard_press(int key, struct s_app *app);

// HIT

struct s_hit_info	ray_hit(t_bvh_elem_box *box, const t_ray *ray);

t_hit_info	elem_inf_hit(const struct s_scene *scene, const t_ray *ray);
t_hit_info	cmp_hit_info(t_hit_info a, t_hit_info b);


struct s_hit_info	ray_hit_sphere(const struct s_ray *ray, const void *elem);
struct s_hit_info	ray_hit_cylinder(const struct s_ray *ray, const void *elem);
struct s_hit_info	ray_hit_cone(const struct s_ray *ray, const void *elem);
struct s_hit_info	ray_hit_plane(const struct s_ray *ray, const void *elem);


double	plane_dst(const struct s_ray *ray, const t_double3 normal, const t_double3 point);


// DRAW
void    draw_pixel_to_img(struct s_img *img, int x, int y, int color);

// UTIL
double				closest_hit_dst_dbl(const double a, const double b);
double				closest_hit_dst_sol2(t_sol2 sol);

t_color_linear 		phong_effect(struct s_scene *scene, t_hit_info *hit_info);
t_color_linear		basic_render(struct s_app *app, double x, double y);
t_color_linear		antialiasing(struct s_app *app, double x, double y);





#endif