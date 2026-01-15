/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:57:28 by echatela          #+#    #+#             */
/*   Updated: 2026/01/15 17:35:49 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_H
# define RUN_H

# include "minirt.h"


int run_scene(struct s_app *app);
int	render(struct s_app *app);

void	 complete_scene(struct s_app *app, struct s_scene *scene);


// RENDER
void 			*render_routine(void *p);

t_color_linear	trace(struct s_scene *scene, t_ray *ray);

// EVENTS
int				event_keyboard_press(int key, struct s_app *app);
int				event_mouse_close(struct s_app *app);

int				event_mouse_release(int button, int x, int y, struct s_app *app);
int				event_mouse_click(int button, int x, int y, struct s_app *app);

int				event_mouse_motion(int x, int y, struct s_app *app);
void			update_mouse(struct s_mouse *mouse, int button, int x, int y);
void			update_mouse_nobutton(struct s_mouse *mouse, int x, int y);

void			bvh_update_coord(t_bvh_base *tree, t_int2 offset);

void			update_cam_dir_xy(struct s_camera *camera, t_real2 value);
void			update_cam_pos_xy(struct s_camera *camera, t_real2 value);

void			update_camera_z(struct s_camera *camera, t_real value);



// DRAW
// void  			draw_pixel_to_img(struct s_img *img, int x, int y, int color);
void    		draw_pixel_to_img(struct s_img *img, t_int2 resolution, t_int2 pos, int color);


#endif
