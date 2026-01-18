/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:57:28 by echatela          #+#    #+#             */
/*   Updated: 2026/01/18 23:07:37 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_H
# define RUN_H

# include "minirt.h"


int run_scene(struct s_app *app);
int	render(struct s_app *app);

void	setup_shapes(struct s_app *app, struct s_scene *scene);


// RENDER
void 			*render_routine(void *p);
t_color_linear	trace(struct s_scene *scene, t_ray *ray);

// EVENTS
int		event_keyboard_press(int key, struct s_app *app);
int		event_mouse_close(struct s_app *app);
int		event_mouse_click(int button, int x, int y, struct s_app *app);
int		event_mouse_release(int button, int x, int y, struct s_app *app);
int		idle_scroll_reenable(void *p);
int		event_mouse_motion(int x, int y, struct s_app *app);
void	update_mouse_position(struct s_mouse *mouse, int button, int x, int y);
void	update_mouse_position_nobutton(struct s_mouse *mouse, int x, int y);
void	update_antialiasing(int key, struct s_app *app);
void	update_zoom_speed(int key, struct s_app *app);
void	update_shapes_coord(t_bvh_base *tree, t_int2 offset);
void	update_camera(struct s_app *app, struct s_camera *camera);

void	camera_view(struct s_app *app, struct s_camera *camera, t_real2 value);
void	camera_pan(struct s_app *app, struct s_camera *camera, struct s_mouse *mouse);
void	camera_zoom(struct s_app *app, struct s_camera *camera, t_real value);
void	draw_pixel_to_img(struct s_img *img, t_int2 resolution, t_int2 pos, int color);

void	setup_viewport(struct s_app *app, struct s_camera *camera);

void	toggle_antialiasing(struct s_antialiasing *a);

void	toggle_downsampling(t_antialiasing *a);
void	increase_downsampling(t_antialiasing *a);
void	decrease_downsampling(t_antialiasing *a);

void	start_downsampling(t_antialiasing *a);
void	stop_downsampling(t_antialiasing *a);

void	render_tile(struct s_app *app, t_int2 tile, render_fn rend);
void	render_tile_downsampled(struct s_app *app, t_int2 tile, render_fn rend);

#endif
