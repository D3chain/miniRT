/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 11:04:24 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/19 10:45:20 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

struct s_app;
struct s_scene;

struct s_ray
{
	t_real3	origin;
	t_real3	dir;
};

struct s_hit_info
{
	bool		did_hit;
	t_real		dst;
	t_real3		hit_point;
	t_real3		normal;
	t_material	material;
};

void				init_ray(struct s_app *app, struct s_ray *ray, t_real x, t_real y);
t_hit_info			ray_hit(t_bvh_elem_box *box, const t_ray *ray);

t_hit_info			elem_inf_hit(struct s_scene *scene, t_ray *ray);

t_real				closest_hit_dst_dbl(const t_real a, const t_real b);
t_real				closest_hit_dst_sol2(t_sol2 sol);
t_real				plane_dst(const struct s_ray *ray, const t_real3 normal, const t_real3 point);

t_hit_info			ray_hit_sphere(const struct s_ray *ray, const void *elem);
t_hit_info			ray_hit_cylinder(const struct s_ray *ray, const void *elem);
t_hit_info			ray_hit_cone(const struct s_ray *ray, const void *elem);
t_hit_info			ray_hit_plane(const struct s_ray *ray, const void *elem);

#endif
