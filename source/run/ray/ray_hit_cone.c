#include "minirt.h"

t_hit_info	create_hit(double dst, const t_ray *ray,
	const struct s_cone *cone, t_double3 normal)
{
	t_hit_info	hit;

	hit.did_hit = true;
	hit.dst = dst;
	hit.hit_point = project(ray->origin, ray->dir, dst);
	hit.normal = normal;
	hit.material = cone->material;
	return (hit);
}

static void	compute_cone_quadratic(const struct s_cone *cone, const t_ray *ray,
	t_double3 x, double coefs[3])
{
	double	dir_dot_axis;
	double	x_dot_axis;

	dir_dot_axis = dot(ray->dir, cone->axis);
	x_dot_axis = dot(x, cone->axis);
	coefs[0] = dir_dot_axis * dir_dot_axis - cone->cos2_theta;
	coefs[1] = 2.0 * (dir_dot_axis * x_dot_axis - cone->cos2_theta
		* dot(ray->dir, x));
	coefs[2] = x_dot_axis * x_dot_axis - cone->cos2_theta * dot(x, x);
}

static bool	solve_quadratic(double coefs[3], double *t1, double *t2)
{
	double	discriminant;
	double	sqrt_disc;
	double	tmp;

	discriminant = coefs[1] * coefs[1] - 4.0 * coefs[0] * coefs[2];
	if (discriminant < 0)
		return (false);
	sqrt_disc = sqrt(discriminant);
	*t1 = (- coefs[1] - sqrt_disc) / (2.0 * coefs[0]);
	*t2 = (- coefs[1] + sqrt_disc) / (2.0 * coefs[0]);
	if (*t1 > *t2)
	{
		tmp = *t1;
		*t1 = *t2;
		*t2 = tmp;
	}
	return (true);
}

static bool	is_within_cone_height(const struct s_cone *cone, t_double3 point)
{
	t_double3	apex_to_point;
	double		projection;

	apex_to_point = minus3(point, cone->apex);
	projection = dot(apex_to_point, cone->axis);
	return (projection >= 0.0 && projection <= cone->height);
}

static t_double3	compute_cone_normal(const struct s_cone *cone, t_double3 point)
{
	t_double3	apex_to_point;
	double		projection;
	t_double3	axis_point;

	apex_to_point = minus3(point, cone->apex);
	projection = dot(apex_to_point, cone->axis);
	axis_point = project(cone->apex, cone->axis, projection);
	return (normalize3(minus3(point, axis_point)));
}

static t_hit_info	intersect_cone_body(const t_ray *ray, const struct s_cone *cone)
{
	t_double3	x;
	double		coefs[3];
	double		t[2];
	t_double3	point;

	x = minus3(ray->origin, cone->apex);
	compute_cone_quadratic(cone, ray, x, coefs);
	if (!solve_quadratic(coefs, &t[0], &t[1]))
		return ((t_hit_info){false, -1, {0}, {0}, cone->material});
	if (t[0] > EPSILON)
	{
		point = project(ray->origin, ray->dir, t[0]);
		if (is_within_cone_height(cone, point))
			return (create_hit(t[0], ray, cone, compute_cone_normal(cone, point)));
	}
	if (t[1] > EPSILON)
	{
		point = project(ray->origin, ray->dir, t[1]);
		if (is_within_cone_height(cone, point))
			return (create_hit(t[1], ray, cone, compute_cone_normal(cone, point)));
	}
	return ((t_hit_info){false, -1, {0}, {0}, cone->material});
}

static t_hit_info	intersect_cap(const t_ray *ray, const struct s_cone *cone)
{
	double		denom;
	double		t;
	t_double3	point;
	t_double3	base_to_point;

	denom = dot(ray->dir, cone->axis);
	if (fabs(denom) < EPSILON)
		return ((t_hit_info){false, -1, {0}, {0}, cone->material});
	t = dot(minus3(cone->base, ray->origin), cone->axis) / denom;
	if (t <= EPSILON)
		return ((t_hit_info){false, -1, {0}, {0}, cone->material});
	point = project(ray->origin, ray->dir, t);
	base_to_point = minus3(point, cone->base);
	if (dot(base_to_point, base_to_point) <= cone->radius_sq)
		return (create_hit(t, ray, cone, cone->axis));
	return ((t_hit_info){false, -1, {0}, {0}, cone->material});
}

struct s_hit_info	ray_hit_cone(const struct s_ray *ray, const void *elem)
{
	const struct s_cone	cone = ((struct s_elem *)elem)->u.cone;
	t_hit_info		body_hit;
	t_hit_info		cap_hit;

	// body_hit = intersect_cone_body(ray, &cone);
	cap_hit = intersect_cap(ray, &cone);
	if (body_hit.did_hit && cap_hit.did_hit)
	{
		if (body_hit.dst < cap_hit.dst)
			return (body_hit);
		return (cap_hit);
	}
	if (body_hit.did_hit)
		return (body_hit);
	if (cap_hit.did_hit)
		return (cap_hit);
	return ((t_hit_info){false, -1, {0}, {0}, cone.material});
}
