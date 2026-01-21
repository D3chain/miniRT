/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:18:50 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/21 17:13:38 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

# include "minirt.h"

typedef enum e_divide_axis	t_div_axis;

enum e_bvh_type
{
	ELEM_BOX,
	NODE_BOX
};

enum e_divide_axis
{
	DIV_ALONG_X = 1,
	DIV_ALONG_Y = 2,
	DIV_ALONG_Z = 4
};

struct s_bounding_box
{
	t_real3	beg;
	t_real3	end;
};

struct s_bvh_base
{
	int				type;
	t_boundbox		bbox;
};

struct s_bvh_elem_box
{
	int				type;
	t_boundbox		bbox;

	int				n_elems;
	t_shape			*elems;
};

struct s_bvh_node
{
	int				type;
	t_boundbox		bbox;

	t_bvh_base		*left;
	t_bvh_base		*right;
};

/*	Construction of the BVH tree	*/
void		bvh_build(t_app *app, t_scene *scene);
void		sort_shapes(t_bvh_elem_box *cur_box, t_div_axis div_axis);
void		bound_boxes(t_bvh_base *node);
t_boundbox	elem_bounding_box(t_shape *elem);

/*	Destruction of the BVH tree		*/
void		bvh_destroy(t_bvh_base *root);

/*	Traversal of the BVH and hit analysis	*/
bool		bvh_any_hit(t_bvh_base *tree, t_ray *ray, t_real max_dist);
bool		elem_inf_any_hit(t_scene *scene, t_ray *ray, t_real max_dist);
bool		collision_aabb(t_bvh_node *node, t_ray *ray);
bool		collision_aabb_base(t_bvh_base *base, t_ray *ray);

#endif
