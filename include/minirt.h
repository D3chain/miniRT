/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:53:10 by echatela          #+#    #+#             */
/*   Updated: 2025/11/13 15:22:55 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

enum {
	AMBIENT_LIGHTNING,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
};

struct s_point
{
	double	x;
	double	y;
	double	z;
};

struct s_rgb
{
	int	r;
	int	g;
	int	b;
};

struct s_vec
{
	double	x;
	double	y;
	double	z;
};

struct s_elem
{
	int		type;
};


struct s_ambient_lightning
{
	int				type;
	double			ratio;
	struct s_rgb	color;
};

struct s_camera
{
	struct s_point	coord;
	struct s_vec	vector;
	int				fov;
};

struct s_light
{
	struct s_point	coord;
	double			ratio;
};

struct s_sphere
{
	struct s_point	coord;
	double			diametre;
	struct s_rgb	color;
};

struct s_plane
{
	struct s_point	coord;
	struct s_vec	vector;
};

struct s_cylinder
{
	struct s_point	coord;
	struct s_vec	vector;
	double			diametre;
	double			height;
	struct s_rgb	color;
};

struct s_scene
{
	struct s_elem	**elem
};

