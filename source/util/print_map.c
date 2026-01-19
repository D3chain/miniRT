/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 13:01:15 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/19 15:48:53 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_pl(struct s_elem *e, int fd)
{
	struct s_plane	*plane = (struct s_plane *) e;
	
	dprintf(fd, "pl\t"REAL3"\t"REAL3"\t"COLOR_RGB"\n",
		e->u.plane.coord.x,
		e->u.plane.coord.y,
		e->u.plane.coord.z,
		e->u.plane.normal.x,
		e->u.plane.normal.y,
		e->u.plane.normal.z,
		e->u.plane.material.color.s_rgb.r,
		e->u.plane.material.color.s_rgb.g,
		e->u.plane.material.color.s_rgb.b
	);
}

static void	print_planes(int fd, struct s_scene *scene)
{
	int			i;

	i = -1;
	while (++i < scene->n_elem_inf)
		print_pl(&scene->elems_inf[i], fd);	
	dprintf(fd, "\n");
}

static void	print_bvh_rec(int fd, t_bvh_base *node)
{
	if (node->type == NODE_BOX)
	{
		print_bvh_rec(fd, (t_bvh_base *)((t_bvh_node *)node)->left);
		print_bvh_rec(fd, (t_bvh_base *)((t_bvh_node *)node)->right);
	}
	else
		print_shapes(fd, (t_bvh_elem_box *)node);
}

static int	new_file(struct s_app *app)
{
	char			new_name[MAX_NAME_LEN];
	char			*filename;
	const time_t	now = time(NULL);
	const struct tm	*t = localtime(&now);
	int				fd;

	filename = ft_strdup(app->file_name);
	if (!filename)
		return (-1);
	*ft_strstr(filename, ".rt") = '\0';
	snprintf(new_name, sizeof(new_name), "%s_%04d%02d%02d_%02d%02d%02d.rt",
		filename,
		t->tm_year + 1900,
		t->tm_mon + 1,
		t->tm_mday,
		t->tm_hour,
		t->tm_min,
		t->tm_sec);
	fd = open(new_name, O_WRONLY | O_CREAT, 0644);
	return (free(filename), fd);
}

void	print_map(struct s_app *app)
{
	const int		fd = new_file(app);

	if (fd == -1)
		printf("Snapshot failed!\n");
	else
	{
		print_RCAL(app, fd);
		print_planes(fd, &app->scene);
		print_bvh_rec(fd, app->scene.bvh_root);
		printf("Snapshot saved!\n");
		close(fd);
	}
}
