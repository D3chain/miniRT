/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 11:52:18 by fox               #+#    #+#             */
/*   Updated: 2026/01/12 14:36:16 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

# include "minirt.h"

enum e_bvh_type
{
	ELEM_BOX,
	NODE_BOX
};

typedef enum e_divide_axis
{
	DIV_ALONG_X = 1,
	DIV_ALONG_Y = 2,
	DIV_ALONG_Z = 4
} t_div_axis;

typedef t_double3	t_point3;

typedef struct s_bounding_box
{
	t_point3	beg;
	t_point3	end;
} t_boundbox;

typedef struct s_bvh_base
{
	int				type;
	t_boundbox		bbox;
} t_bvh_base;

typedef struct s_bvh_elem_box
{
	int				type;
	t_boundbox		bbox;

	int				n_elems;
	struct s_elem	*elems;
} t_bvh_elem_box;

typedef struct s_bvh_node
{
	int				type;
	t_boundbox		bbox;

	t_bvh_base		*left;
	t_bvh_base		*right;
	
} t_bvh_node;


/*	FUNCTIONS	*/

void		bvh_build(struct s_app *app, struct s_scene *scene);

void		sort_elems(t_bvh_elem_box *cur_box, t_div_axis div_axis);

void		bound_boxes(t_bvh_base *node);
t_boundbox	elem_bounding_box(struct s_elem *elem);

t_hit_info	bvh_traverse(t_bvh_base *tree, const t_ray *ray);
bool		bvh_any_hit(t_bvh_base *tree, const t_ray *ray, double max_dist);
bool		elem_inf_any_hit(const struct s_scene *scene, const t_ray *ray, double max_dist);



bool		collision_aabb(t_bvh_node *node, t_ray *ray);
bool		collision_aabb_base(t_bvh_base *base, t_ray *ray);

void		print_tree(t_bvh_base *root, int depth);


#endif
