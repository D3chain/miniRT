/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:57:28 by echatela          #+#    #+#             */
/*   Updated: 2026/01/21 14:48:01 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_H
# define RUN_H

# include "minirt.h"

int run_scene(t_app *app);
int	render(t_app *app);

void	setup_shapes(t_app *app, t_scene *scene);


// RENDER
void 		*render_routine(void *p);
t_color_lin	trace(t_scene *scene, t_ray *ray);

// EVENTS
int		event_keyboard_press(int key, t_app *app);
int		event_mouse_close(t_app *app);
int		event_mouse_click(int button, int x, int y, t_app *app);
int		event_mouse_release(int button, int x, int y, t_app *app);
int		idle_scroll_reenable(void *p);
int		event_mouse_motion(int x, int y, t_app *app);
void	update_mouse_position(t_mouse *mouse, int button, int x, int y);
void	update_mouse_position_nobutton(t_mouse *mouse, int x, int y);
void	update_antialiasing(int key, t_app *app);
void	update_zoom_speed(int key, t_app *app);
void	update_shapes_coord(t_camera *camera, t_bvh_base *tree, t_int2 offset);
void	update_camera(t_app *app, t_camera *camera);

void	camera_view(t_app *app, t_camera *camera, t_real2 value);
void	camera_pan(t_app *app, t_camera *camera, t_mouse *mouse);
void	camera_zoom(t_app *app, t_camera *camera, t_real value);
void	draw_pixel_to_img(t_img *img, t_int2 resolution, t_int2 pos, int color);

void	setup_viewport(t_app *app, t_camera *camera);

void	toggle_antialiasing(struct s_antialiasing *a);

void	toggle_downsampling(t_antialiasing *a);
void	increase_downsampling(t_antialiasing *a);
void	decrease_downsampling(t_antialiasing *a);

void	start_downsampling(t_antialiasing *a);
void	stop_downsampling(t_antialiasing *a);

void	render_tile(t_app *app, t_int2 tile);
void	render_tile_downsampled(t_app *app, t_int2 tile);

#endif
