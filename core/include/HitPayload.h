#ifndef HITPAYLOAD_H
#define HITPAYLOAD_H

#include "Ray.h"
#include "Vec3.h"
#include <memory>

class material;

class hit_payload
{
public:
	vec3 loc;
	vec3 norm;
	std::shared_ptr<material> mat;
	double t;
	bool front_face = false;
	hit_payload() = default;
	hit_payload(vec3 loc, vec3 norm, double t) 
		: loc(loc), norm(norm), t(t), front_face(false) {}
	hit_payload(vec3&& loc, vec3&& norm, double&& t)
		: loc(std::move(loc)), norm(std::move(norm)), t(std::move(t)), front_face(false) {}
	void set_face_normal(const ray& r, const vec3& outward_normal);
};

#endif // HITPAYLOAD_H