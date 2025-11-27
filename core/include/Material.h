#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.h"
#include "Ray.h"
#include "HitPayload.h"

enum MaterialType {
	RANDOM_REFLECT,
	METAL,
	LAMBERTIAN,
	DIALECTRIC
};

class material
{
private:
	double metal_fuzzy_factor;
	double dialectric_refractive_index;
public:
	color albedo;
	MaterialType mat_type;
	bool normal_colors = false;

	material(color albedo, MaterialType mat_type) 
		: albedo(albedo), mat_type(mat_type) {}

	bool scatter(const ray& ray_in, const hit_payload& payload, color& attenuation, ray& ray_out);

	bool set_metal_fuzzy_factor(double in_metal_fuzzy_factor);

	bool set_dialectric_refractive_index(double in_dialectric_refractive_index);
};

#ifndef DIALECTRIC_INDEXES
#define DIALECTRIC_INDEXES

namespace indexes 
{
	const double AIR = 1.0003;
	const double WATER = 1.333;
	const double FUSED_SILICA = 1.458;
	const double GLASS = 1.5;
}

#endif // DIALECTRIC_INDEXES

#endif // MATERIAL_H