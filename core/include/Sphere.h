#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"
#include "Ray.h"
#include "Vec3.h"
#include "Material.h"

class sphere : public hittable
{
private:
	double radius;
	vec3 center;
	std::shared_ptr<material> mat;
public:
	sphere(vec3& center, double radius, std::shared_ptr<material> mat) : center(center), radius(std::fmax(0, radius)), mat(mat) {}
	sphere(vec3&& center, double&& radius, std::shared_ptr<material> mat) : center(center), radius(std::fmax(0, radius)), mat(mat) {}
	sphere(vec3&& center, double&& radius) 
		: center(std::move(center)), radius(std::move(radius)) {}
	virtual bool hit(const ray& r, interval t_min_max, hit_payload& pay) const override;

	void set_material(std::shared_ptr<material> in_mat);
};

#endif // SPHERE_H