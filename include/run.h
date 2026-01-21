/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:57:28 by echatela          #+#    #+#             */
/*   Updated: 2026/01/21 17:16:50 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_H
# define RUN_H

# include "stdbool.h"
# include "minirt_typedef.h"
# include "types.h"

typedef t_color_lin		(*t_render_fn)(t_app*, t_real, t_real);
typedef void			(*t_tile_fn)(t_app *app, t_int2 tile);

//	ANTIALIASING
struct s_thread
{
	pthread_t		*th_tab;
	_Atomic int		th_idx;
	int				cpu_cores;
};

struct s_antialiasing
{
	t_render_fn		rfn;
	t_tile_fn		tfn;

	bool			enabled;
	int				samples;
	int				grid_size;
	t_real			inv_samples;
	t_real			inv_grid_size;
	t_real			offset_factor;

	bool			downsample_activation;
	bool			downsample_state;
	int				downsample_rate;
};

struct s_render
{
	int				resolution;	
	int				n_tiles;
	int				tile_side;
	t_real			inv_tile_side;
	int				tile_area;

	t_antialiasing	antialiasing;
};

/*	run	*/
int			run_scene(t_app *app);
int			render(t_app *app);

/*	run/render	*/
void		*render_routine(void *p);
void		render_tile(t_app *app, t_int2 tile);
void		render_tile_downsampled(t_app *app, t_int2 tile);
t_color_lin	trace(t_scene *scene, t_ray *ray);

t_color_lin	basic_render(t_app *app, t_real x, t_real y);
t_color_lin	antialiasing(t_app *app, t_real x, t_real y);
void		draw_pixel_to_img(t_img *img, t_int2 resolution, \
											t_int2 pos, int color);

/*	run/event	*/
int			event_keyboard(int key, t_app *app);
int			event_mouse_release(int button, int x, int y, t_app *app);
int			event_mouse_motion(int x, int y, t_app *app);

int			event_mouse_click(int button, int x, int y, t_app *app);
int			event_mouse_close(t_app *app);
int			idle_scroll_reenable(void *p);

void		toggle_antialiasing(struct s_antialiasing *a);

void		toggle_downsampling(t_antialiasing *a);
void		increase_downsampling(t_antialiasing *a);
void		decrease_downsampling(t_antialiasing *a);
void		start_downsampling(t_antialiasing *a);
void		stop_downsampling(t_antialiasing *a);

void		camera_view(t_app *app, t_camera *camera, t_real2 value);
void		camera_pan(t_app *app, t_camera *camera, t_mouse *mouse);
void		camera_zoom(t_app *app, t_camera *camera, t_real value);

/*	run/event/update	*/
void		update_mouse_position(t_mouse *mouse, int button, int x, int y);
void		update_mouse_position_nobutton(t_mouse *mouse, int x, int y);
void		update_antialiasing(int key, t_app *app);
void		update_zoom_speed(int key, t_app *app);
void		update_shapes_coord(t_camera *camera, t_bvh_base *tree, \
																t_int2 offset);
void		update_camera(t_app *app, t_camera *camera);

/*	run/setup	*/
void		setup_viewport(t_app *app, t_camera *camera);
void		setup_shapes(t_app *app, t_scene *scene);

void		setup_rcal(t_app *app);
void		setup_r(t_app *app, t_screen *screen);
void		setup_a(t_app *app, t_ambient *ambient);
void		setup_c(t_app *app, t_camera *camera, bool setup_pan_speed);
void		setup_l(t_app *app, t_light *light);

void		setup_pl(t_app *app, t_shape *elem);
void		setup_sp(t_app *app, t_shape *elem);
void		setup_cy(t_app *app, t_shape *elem);
void		setup_co(t_app *app, t_shape *elem);

#endif
