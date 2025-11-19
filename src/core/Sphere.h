#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"
#include "Ray.h"
#include "Vec3.h"

class sphere : public hittable
{
private:
	double radius;
	vec3 center;
public:
	sphere(vec3& center, double radius) : center(center), radius(std::fmax(0, radius)) {}
	sphere(vec3&& center, double&& radius) 
		: center(std::move(center)), radius(std::move(radius)) {}
	virtual bool hit(const ray& r, interval t_min_max, hit_payload& pay) const override;
};

#endif // SPHERE_H