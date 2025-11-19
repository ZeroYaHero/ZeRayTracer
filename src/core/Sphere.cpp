#include "Sphere.h"
#include "Ray.h"

bool sphere::hit(const ray& r, interval t_min_max, hit_payload& pay) const
{
	auto oc = center - r.origin();
	auto a = vec3::dot(r.direction(), r.direction());
	auto b = vec3::dot(r.direction(), oc);
	auto c = vec3::dot(oc, oc) - (radius * radius);
	auto discriminant = (b * b) - (a * c);

	if (discriminant < 0)
	{
		return false;
	}
	auto sqrtd = std::sqrt(discriminant); // We use this for the negative and the positive roots so store for later
	auto root = (b - sqrtd) / a;
	if (!t_min_max.surrounds(root))
	{
		// If the root is not within the range (but outside or on it)
		// Try the other sign
		root = (b + sqrtd) / a;
		if (!t_min_max.surrounds(root))
		{
			return false;
		}
	}

	pay.t = root;
	pay.loc = r.at(pay.t);
	//payload.norm = (payload.loc - center) / radius; // Normalizes the vector
	vec3 outward_normal = (pay.loc - center) / radius;
	pay.set_face_normal(r, outward_normal);

	return true;
}