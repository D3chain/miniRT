#include "config.h"
#include "math_util.h"
#include "minirt.h"
#include "scene.h"

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

static t_hit_info	intersect_cone_body(const t_ray *ray, const struct s_cone *cone)
{
	t_double3	x;
	double		coefs[3];
	double		t[2];
	t_double3	point;

	x = minus3(ray->origin, cone->apex);
	compute_cone_quadratic(cone, ray, x, coefs);
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

	body_hit = intersect_cone_body(ray, cone);
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
