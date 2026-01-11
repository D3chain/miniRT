#include "minirt.h"
#include "scene.h"


static t_hit_info intersect_cap(const t_ray *ray, const struct s_cone *cone)
{
	double		denom;
	double		t;
	t_double3	point;
	t_double3	base_to_point;

	denom = dot(ray->dir, cone->axis);
	if (fabs(denom) < EPSILON)
		return ((t_hit_info){false, -1, {0}, {0}, cone->material});

}

struct s_hit_info	ray_hit_cone(const struct s_ray *ray, const void *elem)
{
	const struct s_cone	cone = ((struct s_elem *)elem)->u.cone;
	t_hit_info		body_hit;
	t_hit_info		cap_hit;

	body_hit = intersect_cone_body(ray, cone);
	cap_hit = intersect_cap(ray, cone);
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
