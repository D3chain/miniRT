/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:24:13 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/21 14:58:58 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

struct s_span
{
	t_real3	min;
	t_real3	max;
	t_real3	span;
	int		i;
};

static t_div_axis	get_div_axis(t_bvh_elem_box *cur_box)
{
	struct s_span		s;

	s = (struct s_span){.min = cur_box->elems->u.any.coord, .i = -1};
	s.max = s.min;
	while (++s.i < cur_box->n_elems)
	{
		if (cur_box->elems[s.i].u.any.coord.x < s.min.x)
			s.min.x = cur_box->elems[s.i].u.any.coord.x;
		if (cur_box->elems[s.i].u.any.coord.x > s.max.x)
			s.max.x = cur_box->elems[s.i].u.any.coord.x;
		if (cur_box->elems[s.i].u.any.coord.y < s.min.y)
			s.min.y = cur_box->elems[s.i].u.any.coord.y;
		if (cur_box->elems[s.i].u.any.coord.y > s.max.y)
			s.max.y = cur_box->elems[s.i].u.any.coord.y;
		if (cur_box->elems[s.i].u.any.coord.z < s.min.z)
			s.min.z = cur_box->elems[s.i].u.any.coord.z;
		if (cur_box->elems[s.i].u.any.coord.z > s.max.z)
			s.max.z = cur_box->elems[s.i].u.any.coord.z;
	}
	s.span = (t_real3){s.max.x - s.min.x, s.max.y - s.min.y, s.max.z - s.min.z};
	if (s.span.x >= s.span.y && s.span.x >= s.span.z)
		return (DIV_ALONG_X);
	if (s.span.y >= s.span.z)
		return (DIV_ALONG_Y);
	return (DIV_ALONG_Z);
}

static t_bvh_node
	*divide_box(t_app *app, t_bvh_elem_box *cur_box, t_div_axis div_axis)
{
	t_bvh_node	*node;
	int			mid;

	sort_shapes(cur_box, div_axis);
	node = xcalloc(app, sizeof(t_bvh_node));
	if (app->status)
		return (NULL);
	node->type = NODE_BOX;
	node->left = xcalloc(app, sizeof(t_bvh_elem_box));
	if (app->status)
		return (NULL);
	node->left->type = ELEM_BOX;
	node->right = xcalloc(app, sizeof(t_bvh_elem_box));
	if (app->status)
		return (NULL);
	node->right->type = ELEM_BOX;
	mid = cur_box->n_elems / 2;
	((t_bvh_elem_box *)(node->left))->n_elems = mid;
	((t_bvh_elem_box *)(node->right))->n_elems = cur_box->n_elems - mid;
	((t_bvh_elem_box *)(node->left))->elems = cur_box->elems;
	((t_bvh_elem_box *)(node->right))->elems = cur_box->elems + mid;
	return (free(cur_box), node);
}

static t_bvh_base	*bvh_subdivide(t_app *app, t_bvh_elem_box *cur_box)
{
	t_bvh_node	*node;

	if (cur_box->n_elems <= BVH_MIN_ELEM)
		return ((t_bvh_base *)cur_box);
	else
	{
		node = divide_box(app, cur_box, get_div_axis(cur_box));
		if (app->status)
			return (NULL);
		node->left = bvh_subdivide(app, (t_bvh_elem_box *)node->left);
		node->right = bvh_subdivide(app, (t_bvh_elem_box *)node->right);
		return ((t_bvh_base *)node);
	}
}

void	bvh_build(t_app *app, t_scene *scene)
{
	scene->bvh_root = xcalloc(app, sizeof(t_bvh_elem_box));
	if (app->status)
		return ;
	((t_bvh_elem_box *)scene->bvh_root)->type = ELEM_BOX;
	((t_bvh_elem_box *)scene->bvh_root)->elems = scene->elems;
	((t_bvh_elem_box *)scene->bvh_root)->n_elems = scene->n_elem;
	scene->bvh_root = bvh_subdivide(app, (t_bvh_elem_box *)scene->bvh_root);
	if (!app->status)
		bound_boxes(scene->bvh_root);
}
